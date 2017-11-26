#include "../../../lv_conf.h"
#if  USE_LV_FONT_SYMBOL_20_FILE != 0
#include <stdint.h>
#include "../lv_font.h"

/*Store the image of the letters (glyph) */
static const uint8_t symbol_20_file_bitmap[] = 
{
    // ASCII: 57376, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x0f, 0x80,  // ------------OOOOO.......
    0x00, 0x7f, 0x80,  // ---------OOOOOOOO.......
    0x03, 0xff, 0x80,  // ------OOOOOOOOOOO.......
    0x03, 0xff, 0x80,  // ------OOOOOOOOOOO.......
    0x03, 0xff, 0x80,  // ------OOOOOOOOOOO.......
    0x03, 0xff, 0x80,  // ------OOOOOOOOOOO.......
    0x03, 0xf0, 0x80,  // ------OOOOOO----O.......
    0x03, 0x80, 0x80,  // ------OOO-------O.......
    0x02, 0x00, 0x80,  // ------O---------O.......
    0x02, 0x00, 0x80,  // ------O---------O.......
    0x02, 0x00, 0x80,  // ------O---------O.......
    0x02, 0x1f, 0x80,  // ------O----OOOOOO.......
    0x02, 0x3f, 0x80,  // ------O---OOOOOOO.......
    0x02, 0x3f, 0x80,  // ------O---OOOOOOO.......
    0x7e, 0x1f, 0x00,  // -OOOOOO----OOOOO-.......
    0xfe, 0x00, 0x00,  // OOOOOOO----------.......
    0xfe, 0x00, 0x00,  // OOOOOOO----------.......
    0x7c, 0x00, 0x00,  // -OOOOO-----------.......

    // ASCII: 57377, char width: 21
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0xff, 0xff, 0xf8,  // OOOOOOOOOOOOOOOOOOOOO...
    0xcc, 0x00, 0x88,  // OO--OO----------O---O...
    0x88, 0x00, 0x88,  // O---O-----------O---O...
    0xd8, 0x00, 0xd8,  // OO-OO-----------OO-OO...
    0xf8, 0x00, 0xf8,  // OOOOO-----------OOOOO...
    0xc8, 0x00, 0x88,  // OO--O-----------O---O...
    0x88, 0x00, 0x88,  // O---O-----------O---O...
    0xcc, 0x01, 0x88,  // OO--OO---------OO---O...
    0xff, 0xff, 0xf8,  // OOOOOOOOOOOOOOOOOOOOO...
    0xcc, 0x01, 0xc8,  // OO--OO---------OOO--O...
    0x88, 0x00, 0x88,  // O---O-----------O---O...
    0xc8, 0x00, 0x88,  // OO--O-----------O---O...
    0xf8, 0x00, 0xf8,  // OOOOO-----------OOOOO...
    0xd8, 0x00, 0xd8,  // OO-OO-----------OO-OO...
    0x88, 0x00, 0x88,  // O---O-----------O---O...
    0x88, 0x00, 0x88,  // O---O-----------O---O...
    0xdc, 0x01, 0xd8,  // OO-OOO---------OOO-OO...
    0x7f, 0xff, 0xf8,  // -OOOOOOOOOOOOOOOOOOOO...

    // ASCII: 57378, char width: 16
    0x00, 0x00,  // ----------------
    0x00, 0x00,  // ----------------
    0x07, 0xe0,  // -----OOOOOO-----
    0x0c, 0x30,  // ----OO----OO----
    0xff, 0xff,  // OOOOOOOOOOOOOOOO
    0x70, 0x0e,  // -OOO--------OOO-
    0x60, 0x04,  // -OO----------O--
    0x60, 0x04,  // -OO----------O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x6d, 0xa4,  // -OO-OO-OO-O--O--
    0x60, 0x04,  // -OO----------O--
    0x60, 0x04,  // -OO----------O--
    0x3f, 0xfc,  // --OOOOOOOOOOOO--
    0x00, 0x00,  // ----------------
    0x00, 0x00,  // ----------------

    // ASCII: 57379, char width: 19
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x0f, 0xfc, 0x00,  // ----OOOOOOOOOO-----.....
    0x0f, 0xfe, 0x00,  // ----OOOOOOOOOOO----.....
    0x07, 0xfc, 0x00,  // -----OOOOOOOOO-----.....
    0x03, 0xf8, 0x00,  // ------OOOOOOO------.....
    0x01, 0xf0, 0x00,  // -------OOOOO-------.....
    0x00, 0xe0, 0x00,  // --------OOO--------.....
    0xfe, 0x4f, 0xc0,  // OOOOOOO--O--OOOOOO-.....
    0xff, 0x1f, 0xc0,  // OOOOOOOO---OOOOOOO-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0xff, 0xfb, 0x40,  // OOOOOOOOOOOOO-OO-O-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0x00, 0x00,  // -------------------.....

    // ASCII: 57380, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x1f, 0xfc, 0x00,  // ---OOOOOOOOOOO---.......
    0x3f, 0xfe, 0x00,  // --OOOOOOOOOOOOO--.......
    0x30, 0x06, 0x00,  // --OO---------OO--.......
    0x30, 0x07, 0x00,  // --OO---------OOO-.......
    0x70, 0x03, 0x00,  // -OOO----------OO-.......
    0x60, 0x03, 0x00,  // -OO-----------OO-.......
    0xe0, 0x03, 0x80,  // OOO-----------OOO.......
    0xe0, 0x03, 0x80,  // OOO-----------OOO.......
    0xfc, 0x1f, 0x80,  // OOOOOO-----OOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57381, char width: 21
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0xff, 0xff, 0xf8,  // OOOOOOOOOOOOOOOOOOOOO...
    0x80, 0x00, 0x08,  // O-------------------O...
    0x8c, 0x00, 0x08,  // O---OO--------------O...
    0x9e, 0x00, 0x08,  // O--OOOO-------------O...
    0x9e, 0x06, 0x08,  // O--OOOO------OO-----O...
    0x9e, 0x0f, 0x08,  // O--OOOO-----OOOO----O...
    0x80, 0x1f, 0x88,  // O----------OOOOOO---O...
    0x80, 0x3f, 0xc8,  // O---------OOOOOOOO--O...
    0x82, 0x7f, 0xe8,  // O-----O--OOOOOOOOOO-O...
    0x87, 0xff, 0xe8,  // O----OOOOOOOOOOOOOO-O...
    0x8f, 0xff, 0xe8,  // O---OOOOOOOOOOOOOOO-O...
    0x9f, 0xff, 0xe8,  // O--OOOOOOOOOOOOOOOO-O...
    0x9f, 0xff, 0xe8,  // O--OOOOOOOOOOOOOOOO-O...
    0x80, 0x00, 0x08,  // O-------------------O...
    0x80, 0x00, 0x08,  // O-------------------O...
    0xff, 0xff, 0xf8,  // OOOOOOOOOOOOOOOOOOOOO...
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...

    // ASCII: 57382, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x1c, 0x00,  // -----------OOO---.......
    0x00, 0x3e, 0x00,  // ----------OOOOO--.......
    0x00, 0x1f, 0x00,  // -----------OOOOO-.......
    0x00, 0xcf, 0x80,  // --------OO--OOOOO.......
    0x01, 0xe7, 0x80,  // -------OOOO--OOOO.......
    0x03, 0xf3, 0x00,  // ------OOOOOO--OO-.......
    0x07, 0xf8, 0x00,  // -----OOOOOOOO----.......
    0x0f, 0xfc, 0x00,  // ----OOOOOOOOOO---.......
    0x1f, 0xf8, 0x00,  // ---OOOOOOOOOO----.......
    0x3f, 0xf0, 0x00,  // --OOOOOOOOOO-----.......
    0x7f, 0xe0, 0x00,  // -OOOOOOOOOO------.......
    0xff, 0xc0, 0x00,  // OOOOOOOOOO-------.......
    0xcf, 0x80, 0x00,  // OO--OOOOO--------.......
    0xc7, 0x00, 0x00,  // OO---OOO---------.......
    0xee, 0x00, 0x00,  // OOO-OOO----------.......
    0xfc, 0x00, 0x00,  // OOOOOO-----------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57383, char width: 11
    0x00, 0x00,  // -----------.....
    0xe0, 0x00,  // OOO--------.....
    0xe0, 0x20,  // OOO-------O.....
    0xe0, 0x60,  // OOO------OO.....
    0xe0, 0xe0,  // OOO-----OOO.....
    0xe1, 0xe0,  // OOO----OOOO.....
    0xe3, 0xe0,  // OOO---OOOOO.....
    0xe7, 0xe0,  // OOO--OOOOOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xef, 0xe0,  // OOO-OOOOOOO.....
    0xe7, 0xe0,  // OOO--OOOOOO.....
    0xe3, 0xe0,  // OOO---OOOOO.....
    0xe1, 0xe0,  // OOO----OOOO.....
    0xe0, 0xe0,  // OOO-----OOO.....
    0xe0, 0x60,  // OOO------OO.....
    0xe0, 0x20,  // OOO-------O.....
    0x00, 0x00,  // -----------.....
    0x00, 0x00,  // -----------.....

    // ASCII: 57384, char width: 16
    0x00, 0x00,  // ----------------
    0x80, 0x00,  // O---------------
    0xe0, 0x00,  // OOO-------------
    0xf8, 0x00,  // OOOOO-----------
    0xfc, 0x00,  // OOOOOO----------
    0xff, 0x00,  // OOOOOOOO--------
    0xff, 0xc0,  // OOOOOOOOOO------
    0xff, 0xf0,  // OOOOOOOOOOOO----
    0xff, 0xfc,  // OOOOOOOOOOOOOO--
    0xff, 0xfe,  // OOOOOOOOOOOOOOO-
    0xff, 0xfe,  // OOOOOOOOOOOOOOO-
    0xff, 0xf8,  // OOOOOOOOOOOOO---
    0xff, 0xe0,  // OOOOOOOOOOO-----
    0xff, 0xc0,  // OOOOOOOOOO------
    0xff, 0x00,  // OOOOOOOO--------
    0xfc, 0x00,  // OOOOOO----------
    0xf0, 0x00,  // OOOO------------
    0xc0, 0x00,  // OO--------------
    0x00, 0x00,  // ----------------
    0x00, 0x00,  // ----------------

    // ASCII: 57385, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0xfe, 0x3f, 0x80,  // OOOOOOO---OOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57386, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57387, char width: 11
    0x00, 0x00,  // -----------.....
    0x00, 0xe0,  // --------OOO.....
    0x80, 0xe0,  // O-------OOO.....
    0xc0, 0xe0,  // OO------OOO.....
    0xe0, 0xe0,  // OOO-----OOO.....
    0xf0, 0xe0,  // OOOO----OOO.....
    0xf8, 0xe0,  // OOOOO---OOO.....
    0xfc, 0xe0,  // OOOOOO--OOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xff, 0xe0,  // OOOOOOOOOOO.....
    0xfe, 0xe0,  // OOOOOOO-OOO.....
    0xfc, 0xe0,  // OOOOOO--OOO.....
    0xf8, 0xe0,  // OOOOO---OOO.....
    0xf0, 0xe0,  // OOOO----OOO.....
    0xe0, 0xe0,  // OOO-----OOO.....
    0xc0, 0xe0,  // OO------OOO.....
    0x80, 0xe0,  // O-------OOO.....
    0x00, 0x00,  // -----------.....
    0x00, 0x00,  // -----------.....

    // ASCII: 57388, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x01, 0xc0, 0x00,  // -------OOO-------.......
    0x03, 0xe0, 0x00,  // ------OOOOO------.......
    0x07, 0xf0, 0x00,  // -----OOOOOOO-----.......
    0x0f, 0xf8, 0x00,  // ----OOOOOOOOO----.......
    0x1f, 0xfc, 0x00,  // ---OOOOOOOOOOO---.......
    0x3f, 0xfe, 0x00,  // --OOOOOOOOOOOOO--.......
    0x7f, 0xff, 0x00,  // -OOOOOOOOOOOOOOO-.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57389, char width: 20
    0x00, 0x00, 0x00,  // --------------------....
    0x00, 0x00, 0x80,  // ----------------O---....
    0x00, 0x00, 0xc0,  // ----------------OO--....
    0xf8, 0x1f, 0xe0,  // OOOOO------OOOOOOOO-....
    0xfe, 0x7f, 0xf0,  // OOOOOOO--OOOOOOOOOOO....
    0xfe, 0xff, 0xe0,  // OOOOOOO-OOOOOOOOOOO-....
    0x0e, 0xe0, 0xc0,  // ----OOO-OOO-----OO--....
    0x07, 0xc0, 0x80,  // -----OOOOO------O---....
    0x01, 0xc0, 0x00,  // -------OOO----------....
    0x03, 0x80, 0x00,  // ------OOO-----------....
    0x03, 0x80, 0x00,  // ------OOO-----------....
    0x07, 0xe0, 0x80,  // -----OOOOOO-----O---....
    0x0f, 0x60, 0xc0,  // ----OOOO-OO-----OO--....
    0xfe, 0xff, 0xe0,  // OOOOOOO-OOOOOOOOOOO-....
    0xfc, 0x7f, 0xf0,  // OOOOOO---OOOOOOOOOOO....
    0xf8, 0x1f, 0xe0,  // OOOOO------OOOOOOOO-....
    0x00, 0x00, 0xc0,  // ----------------OO--....
    0x00, 0x00, 0x80,  // ----------------O---....
    0x00, 0x00, 0x00,  // --------------------....
    0x00, 0x00, 0x00,  // --------------------....

    // ASCII: 57390, char width: 21
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0x09, 0xff, 0xe0,  // ----O--OOOOOOOOOOOO--...
    0x1c, 0xff, 0xe0,  // ---OOO--OOOOOOOOOOO--...
    0x3e, 0x7f, 0xe0,  // --OOOOO--OOOOOOOOOO--...
    0x7f, 0x00, 0xe0,  // -OOOOOOO--------OOO--...
    0xff, 0x00, 0xe0,  // OOOOOOOO--------OOO--...
    0xff, 0x80, 0xe0,  // OOOOOOOOO-------OOO--...
    0x1c, 0x00, 0xe0,  // ---OOO----------OOO--...
    0x1c, 0x03, 0xf8,  // ---OOO--------OOOOOOO...
    0x1c, 0x07, 0xfc,  // ---OOO-------OOOOOOOOO..
    0x1c, 0x03, 0xf8,  // ---OOO--------OOOOOOO...
    0x1f, 0xf9, 0xf0,  // ---OOOOOOOOOO--OOOOO-...
    0x1f, 0xfc, 0xe0,  // ---OOOOOOOOOOO--OOO--...
    0x1f, 0xfc, 0x40,  // ---OOOOOOOOOOO---O---...
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...
    0x00, 0x00, 0x00,  // ---------------------...

    // ASCII: 57391, char width: 19
    0x00, 0x00, 0x00,  // -------------------.....
    0x3e, 0x00, 0x00,  // --OOOOO------------.....
    0xff, 0x00, 0x00,  // OOOOOOOO-----------.....
    0xff, 0x80, 0x00,  // OOOOOOOOO----------.....
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO--.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xe0,  // OOOOOOOOOOOOOOOOOOO.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0x7f, 0xff, 0xc0,  // -OOOOOOOOOOOOOOOOO-.....
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0x00, 0x00,  // -------------------.....

    // ASCII: 57392, char width: 19
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0xc0, 0x00,  // --------OO---------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x03, 0xf0, 0x00,  // ------OOOOOO-------.....
    0x07, 0xf8, 0x00,  // -----OOOOOOOO------.....
    0x0f, 0xfc, 0x00,  // ----OOOOOOOOOO-----.....
    0x0f, 0xfe, 0x00,  // ----OOOOOOOOOOO----.....
    0x01, 0xf0, 0x00,  // -------OOOOO-------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0x01, 0xe0, 0x00,  // -------OOOO--------.....
    0xfc, 0x0f, 0xc0,  // OOOOOO------OOOOOO-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0xff, 0xfb, 0x40,  // OOOOOOOOOOOOO-OO-O-.....
    0xff, 0xff, 0xc0,  // OOOOOOOOOOOOOOOOOO-.....
    0x00, 0x00, 0x00,  // -------------------.....
    0x00, 0x00, 0x00,  // -------------------.....

    // ASCII: 57393, char width: 20
    0x00, 0x00, 0x00,  // --------------------....
    0x00, 0x00, 0x00,  // --------------------....
    0x00, 0x00, 0x00,  // --------------------....
    0x78, 0x00, 0x00,  // -OOOO---------------....
    0xfe, 0x00, 0x00,  // OOOOOOO-------------....
    0xc3, 0x01, 0xa0,  // OO----OO-------OO-O-....
    0xc1, 0x06, 0x20,  // OO-----O-----OO---O-....
    0xe3, 0x18, 0x40,  // OOO---OO---OO----O--....
    0x7f, 0xe1, 0x80,  // -OOOOOOOOOO----OO---....
    0x1f, 0x83, 0x00,  // ---OOOOOO-----OO----....
    0x00, 0xa4, 0x00,  // --------O-O--O------....
    0x1f, 0x10, 0x00,  // ---OOOOO---O--------....
    0x7f, 0xe0, 0x00,  // -OOOOOOOOOO---------....
    0xf3, 0x18, 0x00,  // OOOO--OO---OO-------....
    0xc1, 0x04, 0x00,  // OO-----O-----O------....
    0xc3, 0x03, 0x00,  // OO----OO------OO----....
    0xc6, 0x00, 0xe0,  // OO---OO---------OOO-....
    0xfe, 0x00, 0x00,  // OOOOOOO-------------....
    0x78, 0x00, 0x00,  // -OOOO---------------....
    0x00, 0x00, 0x00,  // --------------------....

    // ASCII: 57394, char width: 20
    0x03, 0xf8, 0x00,  // ------OOOOOOO-------....
    0x0e, 0x18, 0x00,  // ----OOO----OO-------....
    0x1e, 0x08, 0x00,  // ---OOOO-----O-------....
    0x32, 0x08, 0x00,  // --OO--O-----O-------....
    0x62, 0x0f, 0xf0,  // -OO---O-----OOOOOOOO....
    0xe6, 0x0f, 0xf0,  // OOO--OO-----OOOOOOOO....
    0xfe, 0x1c, 0x10,  // OOOOOOO----OOO-----O....
    0x80, 0x34, 0x10,  // O---------OO-O-----O....
    0x80, 0x64, 0x10,  // O--------OO--O-----O....
    0x80, 0xc4, 0x10,  // O-------OO---O-----O....
    0x81, 0xfc, 0x10,  // O------OOOOOOO-----O....
    0x81, 0x80, 0x10,  // O------OO----------O....
    0x81, 0x80, 0x10,  // O------OO----------O....
    0x81, 0x80, 0x10,  // O------OO----------O....
    0xff, 0x80, 0x10,  // OOOOOOOOO----------O....
    0x03, 0x80, 0x10,  // ------OOO----------O....
    0x01, 0x80, 0x10,  // -------OO----------O....
    0x01, 0x80, 0x10,  // -------OO----------O....
    0x01, 0x80, 0x30,  // -------OO---------OO....
    0x01, 0xff, 0xf0,  // -------OOOOOOOOOOOOO....

    // ASCII: 57395, char width: 17
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......
    0xff, 0xf8, 0x00,  // OOOOOOOOOOOOO----.......
    0x9e, 0x26, 0x00,  // O--OOOO---O--OO--.......
    0x9e, 0x23, 0x00,  // O--OOOO---O---OO-.......
    0x9e, 0x21, 0x00,  // O--OOOO---O----O-.......
    0x9e, 0x21, 0x80,  // O--OOOO---O----OO.......
    0x9f, 0xe0, 0x80,  // O--OOOOOOOO-----O.......
    0x80, 0x00, 0x80,  // O---------------O.......
    0x80, 0x00, 0x80,  // O---------------O.......
    0x80, 0x00, 0x80,  // O---------------O.......
    0x80, 0x00, 0x80,  // O---------------O.......
    0x9f, 0xfc, 0x80,  // O--OOOOOOOOOOO--O.......
    0x90, 0x04, 0x80,  // O--O---------O--O.......
    0x90, 0x04, 0x80,  // O--O---------O--O.......
    0x90, 0x04, 0x80,  // O--O---------O--O.......
    0x90, 0x04, 0x80,  // O--O---------O--O.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0x00, 0x00, 0x00,  // -----------------.......
    0x00, 0x00, 0x00,  // -----------------.......

    // ASCII: 57396, char width: 17
    0xff, 0xc0, 0x00,  // OOOOOOOOOO-------.......
    0xff, 0xd8, 0x00,  // OOOOOOOOOO-OO----.......
    0xff, 0xdc, 0x00,  // OOOOOOOOOO-OOO---.......
    0xff, 0xde, 0x00,  // OOOOOOOOOO-OOOO--.......
    0xff, 0xdf, 0x00,  // OOOOOOOOOO-OOOOO-.......
    0xff, 0xcf, 0x00,  // OOOOOOOOOO--OOOO-.......
    0xff, 0xc0, 0x00,  // OOOOOOOOOO-------.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
    0xff, 0xff, 0x80,  // OOOOOOOOOOOOOOOOO.......
};

/*Store the start index of the glyphs in the bitmap array*/
static const uint32_t symbol_20_file_map[] = 
{
     0, 60, 120, 160, 220, 280, 340, 400, 
    440, 480, 540, 600, 640, 700, 760, 820, 
    880, 940, 1000, 1060, 1120, 
};

/*Store the width (column count) of each glyph*/
static const uint8_t symbol_20_file_width[] = 
{
    17, 21, 16, 19, 17, 21, 17, 11, 
    16, 17, 17, 11, 17, 20, 21, 19, 
    19, 20, 20, 17, 17, 
};

lv_font_t lv_font_symbol_20_file = 
{
#if LV_TXT_UTF8 == 0
    224,        /*First letter's unicode */
    255,        /*Last letter's unicode */
#else
    57376,        /*First letter's unicode */
    57397,        /*Last letter's unicode */
#endif
    20,        /*Letters height (rows) */
    symbol_20_file_bitmap,    /*Glyph's bitmap*/
    symbol_20_file_map,    /*Glyph start indexes in the bitmap*/
    symbol_20_file_width,    /*Glyph widths (columns)*/
};

#endif /*SYMBOL_20_FILE_H*/