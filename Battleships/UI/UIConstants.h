#ifndef UICONSTANTS_H
#define UICONSTANTS_H

class UIConstants {
public:
    static constexpr int CELL_SIZE = 70;
    static constexpr int BOARD_SIZE = 10;
    static constexpr int TOTAL_CATS = 5;

	static constexpr int BOARD_WIDTH = CELL_SIZE * BOARD_SIZE;
	static constexpr int BOARD_HEIGHT = CELL_SIZE * BOARD_SIZE;

    static constexpr int SETUPBOARD_WIDTH = 1400;
	static constexpr int SETUPBOARD_HEIGHT = 750;

    static constexpr int GAMEBOARD_WIDTH = 720;
    static constexpr int GAMEBOARD_HEIGHT = 720;
};

#endif 