#ifndef GAME_GUI_H
#define GAME_GUI_H

class GameGUI
{
public:
	GameGUI(){ button_cood_error_y = 0;};
	void MainBtn ( ) ;
	short SetMainBtn ( ) ;
	void SetMapBtn () ;
	int  GetBtnCodEorY(){ return button_cood_error_y ;};
private:
	int button_cood_error_y;
	
};

#endif