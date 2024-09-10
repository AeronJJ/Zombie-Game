#include "N5110.h"

N5110::N5110(Tileset* tiles, SDL_Window* window, SDL_Surface* screenSurface) : tiles_(tiles), window_(window), screenSurface_(screenSurface) {
}

N5110::N5110(PinName const pwrPin, 
	     PinName const scePin, 
	     PinName const rstPin, 
	     PinName const dcPin,  
	     PinName const mosiPin,
	     PinName const sclkPin,
	     PinName const ledPin) {
  if (!init_()) {
    printf("SDL/Window failed to initialise, SDL_Error: %s\n", SDL_GetError());
    // IDK what to do here to properly close the program... Call the destructor maybe
    // The embedded code always assumes that the initialisation completes successfully, I can add a flag but this code is already convoluted af.
  }
}

N5110::N5110(PinName const scePin, 
	     PinName const rstPin, 
	     PinName const dcPin,  
	     PinName const mosiPin,
	     PinName const sclkPin,
	     PinName const ledPin) {
  if (!init_()) {
    printf("SDL/Window failed to initialise, SDL_Error: %s\n", SDL_GetError());
  }
}


N5110::~N5110() {
  delete tiles_;
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

bool N5110::init_() {
  tiles_ = new Tileset;
  window_ = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
  window_ = SDL_CreateWindow(gameName_, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window_ == NULL) return false;
  screenSurface_ = SDL_GetWindowSurface(window_);
  return true;
}

void N5110::setPixel(unsigned int const x, unsigned int const y, bool const state){
    if (x<WIDTH && y<HEIGHT) {  // check within range
	Tile* tile = tiles_->getTile(y*84 + x);
	tile->set(state);
    }
}

void N5110::refresh(){
	for (int i = 0; i < tiles_->getNum(); i++) {
		Tile* currentTile = tiles_->getTile(i);
		bool col = currentTile->getColour();
		SDL_Rect newRect;
		newRect.w = 10;
		newRect.h = 10;
		newRect.y = 10*floor(i/84);
		newRect.x = 10*i - newRect.y*84;
		if (!col) 
		{
			SDL_FillRect( screenSurface_, &newRect, SDL_MapRGB( screenSurface_->format, 0xFF, 0xFF, 0xFF) );
		}
		else
		{
			SDL_FillRect( screenSurface_, &newRect, SDL_MapRGB( screenSurface_->format, 0x00, 0x00, 0x00) );
		}
	}
	SDL_UpdateWindowSurface( window_ );
}

void N5110::clear(){
	for (int i = 0; i < tiles_->getNum(); i++) {
		tiles_->getTile(i)->set(0);
	}
}

void N5110::drawSprite(int x0, int y0, int nrows, int ncols, int *sprite, bool reverse){
    for (int i = 0; i < nrows; i++) {
        for (int j = 0 ; j < ncols ; j++) {
            int pixel = *((sprite+i*ncols)+j); // This treats sprite as if its a 1 dimensional array
            if (pixel==2) {
              setPixel(x0+j,y0+i, 0);
            }
            else if (pixel==1) {
              setPixel(x0+j, y0+i, 1);
            }
        }
    }
}

void N5110::inverseMode() {

}

void N5110::normalMode() {

}

void N5110::init(LCD_Type lcd) {
  
}

void N5110::setContrast(float contrast) {

}

void N5110::setBrightness(float brightness) {

}


void N5110:: drawCircle(unsigned int const x0, unsigned int const y0, unsigned int const radius, FillType const fill) {
    
    // from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    int x = radius;
    int y = 0;
    int radiusError = 1-x;

    while(x >= y) {

        // if transparent, just draw outline
        if (fill == FILL_TRANSPARENT) {
            setPixel( x + x0,  y + y0,true);
            setPixel(-x + x0,  y + y0,true);
            setPixel( y + x0,  x + y0,true);
            setPixel(-y + x0,  x + y0,true);
            setPixel(-y + x0, -x + y0,true);
            setPixel( y + x0, -x + y0,true);
            setPixel( x + x0, -y + y0,true);
            setPixel(-x + x0, -y + y0,true);
        } else {  

            // drawing filled circle, so draw lines between points at same y value
            int type = (fill==FILL_BLACK) ? 1:0;  // black or white fill
            drawLine(x+x0,y+y0,-x+x0,y+y0,type);
            drawLine(y+x0,x+y0,-y+x0,x+y0,type);
            drawLine(y+x0,-x+y0,-y+x0,-x+y0,type);
            drawLine(x+x0,-y+y0,-x+x0,-y+y0,type);
        }

        y++;
        if (radiusError<0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

void N5110::drawLine(unsigned int const x0, unsigned int const y0, unsigned int const x1, unsigned int const y1, unsigned int const type){
    
    // Note that the ranges can be negative so we have to turn the input values into signed integers first
    int const y_range = static_cast<int>(y1) - static_cast<int>(y0);
    int const x_range = static_cast<int>(x1) - static_cast<int>(x0);

    // if dotted line, set step to 2, else step is 1
    unsigned int const step = (type==2) ? 2:1;

    // make sure we loop over the largest range to get the most pixels on the display
    // for instance, if drawing a vertical line (x_range = 0), we need to loop down the y pixels
    // or else we'll only end up with 1 pixel in the x column
    if ( abs(x_range) > abs(y_range) ) {

        // ensure we loop from smallest to largest or else for-loop won't run as expected
        unsigned int const start = x_range > 0 ? x0:x1;
        unsigned int const stop =  x_range > 0 ? x1:x0;

        // loop between x pixels
        for (unsigned int x = start; x<= stop ; x+=step) {  // do linear interpolation
            int const dx = static_cast<int>(x)-static_cast<int>(x0);
            unsigned int const y = y0 + y_range * dx / x_range;

            // If the line type is '0', this will clear the pixel
            // If it is '1' or '2', the pixel will be set
            setPixel(x,y, type);
        }

    } else {

        // ensure we loop from smallest to largest or else for-loop won't run as expected
        unsigned int const start = y_range > 0 ? y0:y1;
        unsigned int const stop =  y_range > 0 ? y1:y0;

        for (unsigned int y = start; y<= stop ; y+=step) {  // do linear interpolation
            int const dy = static_cast<int>(y)-static_cast<int>(y0);
            unsigned int const x = x0 + x_range * dy / y_range;

            // If the line type is '0', this will clear the pixel
            // If it is '1' or '2', the pixel will be set
            setPixel(x,y, type);
        }
    }
}


void N5110::drawRect(unsigned int const x0, unsigned int const y0, unsigned int const width, unsigned int const height, FillType const fill){
    
    // transparent, just outline
    if (fill == FILL_TRANSPARENT) {
        drawLine(x0,y0,x0+(width-1),y0,1);                          // top
        drawLine(x0,y0+(height-1),x0+(width-1),y0+(height-1),1);    // bottom
        drawLine(x0,y0,x0,y0+(height-1),1);                         // left
        drawLine(x0+(width-1),y0,x0+(width-1),y0+(height-1),1);     // right
    
    } else { // filled rectangle
        int type = (fill==FILL_BLACK) ? 1:0;                        // black or white fill
        for (int y = y0; y<y0+height; y++) {                        // loop through rows of rectangle
            drawLine(x0,y,x0+(width-1),y,type);                     // draw line across screen
        }
    }
}


void N5110::turnOn() { }

void N5110::turnOff() { }

void N5110::setTempCoefficient(char tc) { }

void N5110::setBias(char bias) { }

void N5110::reset() { }

void N5110::initSPI(LCD_Type const lcd) { }

void N5110::sendCommand(unsigned char command) { }

void N5110::sendData(unsigned char data) { }

void N5110::clearRAM() { }

void N5110::setXYAddress(unsigned int const x, unsigned int const y) { }

void N5110::clearPixel(unsigned int const x, unsigned int const y) {
  setPixel(x, y, false);
}

int N5110::getPixel(unsigned int const x, unsigned int const y) const {
  int pos = y * WIDTH + x;
  return tiles_->getTile(pos)->getColour();
}

void N5110::randomiseBuffer() { }

void N5110::printChar(char const c, unsigned int const x, unsigned int const y) {
  //std::cout << "Drawing character " << font5x7[(c-32)*5 + 2] << std::endl;

  unsigned int startY = (y - 1) * 8;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      setPixel(x + i, startY + j, font5x7[(c-32) * 5 + i] & (1 << j));
    }
  }
  /*
  if (y < BANKS) {
    for (int i = 0; i < 5; i++) {
      int pixel_x = x+1;
      if (pixel_x > WIDTH-1) break;
      setPixel(pixel_x, y, font5x7[(c-32)*5 + i]);
    }

    
  }
  */
}

void N5110::printString(const char *str, unsigned int x, unsigned int const y) {
  while (*str) {
    printChar(*str, x, y);
    x += 6;
    str++;
  }
}

void N5110::plotArray(float const array[]) {
    for (int i=0; i<WIDTH; i++) {  // loop through array
        // elements are normalised from 0.0 to 1.0, so multiply
        // by 47 to convert to pixel range, and subtract from 47
        // since top-left is 0,0 in the display geometry
        setPixel(i,47 - int(array[i]*47.0f),true);
    }
}

