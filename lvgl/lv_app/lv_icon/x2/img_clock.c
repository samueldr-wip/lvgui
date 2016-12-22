#include "img_conf.h"
#include "lv_conf.h"

#if USE_IMG_CLOCK != 0 || LV_APP_USE_INTERNAL_ICONS == 2

#include <stdint.h> 
#include "misc/others/color.h"

const color_int_t img_clock [] = { /*Width = 32, Height = 31*/ 
32,	/*Width*/
31,	/*Heigth*/
16,	/*Color depth = 16*/
1,	/*Flags: Transp = 1*/
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 27469, 21162, 19017, 16936, 16904, 19017, 21130, 25388, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 31727, 19049, 12678, 6371, 4258, 2145, 2113, 32, 32, 2113, 2145, 4226, 6371, 10597, 16936, 29582, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 31695, 12678, 32, 0, 0, 0, 2145, 4226, 4258, 4258, 4226, 2145, 32, 0, 0, 0, 10565, 27501, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 19017, 4258, 0, 0, 0, 2113, 12678, 21130, 25356, 27501, 27501, 25388, 21162, 14791, 4226, 0, 0, 0, 4226, 16904, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 21162, 2113, 0, 32, 6371, 12710, 21162, 31727, 40147, 44405, 48599, 46518, 44405, 40179, 33808, 23275, 14823, 8452, 2113, 0, 0, 16904, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 16936, 2113, 0, 0, 12710, 29582, 46486, 54970, 57083, 61277, 63422, 63422, 63390, 61277, 59196, 59164, 57051, 48599, 31727, 16904, 32, 0, 0, 14823, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 27501, 4226, 0, 0, 12678, 31695, 48599, 63390, 65535, 65535, 65535, 61309, 61277, 65535, 65535, 65535, 65535, 65535, 65503, 50744, 33840, 14823, 2113, 0, 2113, 23243, 2016, 2016, 2016, 
2016, 2016, 27469, 8452, 0, 32, 14823, 31727, 52825, 63422, 65535, 65535, 65535, 59196, 40147, 38066, 59164, 65535, 65535, 65535, 65535, 65535, 63422, 54938, 38066, 21130, 2113, 0, 4226, 23243, 2016, 2016, 
2016, 2016, 14791, 0, 0, 8484, 31695, 50712, 65503, 65535, 65535, 65535, 65535, 54970, 23275, 23243, 52825, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 54970, 38034, 10597, 0, 0, 10597, 2016, 2016, 
2016, 2016, 8452, 0, 32, 19017, 48631, 65503, 65535, 65535, 65535, 65535, 65535, 52857, 14791, 12710, 50712, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 23243, 4258, 0, 6339, 29614, 2016, 
2016, 23275, 4226, 0, 10565, 29614, 59164, 65535, 65535, 65535, 65535, 65535, 65535, 50744, 10565, 8484, 48599, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 61277, 35921, 16904, 2113, 2113, 19017, 2016, 
2016, 14791, 32, 4226, 23275, 44373, 61309, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 10597, 10565, 48631, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 63390, 48631, 29614, 6339, 0, 8484, 27501, 
27469, 8452, 0, 6371, 33840, 52857, 63422, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 10597, 10597, 48631, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65503, 59196, 40179, 8484, 0, 2113, 21162, 
23243, 2145, 0, 8484, 42260, 61277, 65503, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 10597, 10597, 50744, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 48599, 10597, 0, 0, 16904, 
19049, 0, 0, 10565, 46486, 65503, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 10597, 8452, 42260, 57083, 57083, 57051, 57051, 59164, 63422, 65535, 65535, 65535, 65535, 52825, 12710, 0, 0, 12710, 
16936, 0, 0, 10597, 48599, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 52825, 10597, 32, 19049, 29582, 29582, 27501, 27469, 35953, 57083, 65535, 65535, 65535, 65535, 52857, 14791, 0, 0, 12678, 
16936, 0, 0, 10597, 46518, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 54938, 21162, 8484, 19017, 23243, 23243, 21162, 19049, 31695, 54970, 65535, 65535, 65535, 65535, 52825, 14791, 0, 0, 12678, 
21130, 32, 0, 10565, 44373, 63390, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 59196, 42260, 33808, 35921, 35953, 35953, 35953, 33840, 42292, 59164, 65535, 65535, 65535, 65535, 50712, 12678, 0, 0, 14823, 
25356, 4258, 0, 8452, 38066, 57083, 63422, 65535, 65535, 65535, 65535, 65535, 65535, 63422, 54970, 50744, 50712, 50712, 50712, 50712, 48631, 52857, 61309, 65535, 65535, 65535, 63390, 44405, 10565, 0, 0, 19049, 
31695, 10597, 0, 6339, 29614, 48631, 63390, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 63422, 63390, 63390, 63390, 63390, 61309, 61309, 63390, 65503, 65535, 65535, 63422, 54938, 35921, 6371, 0, 6339, 25356, 
2016, 19049, 2113, 2113, 19017, 38034, 59196, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 61277, 42292, 23275, 4226, 32, 14791, 33808, 
2016, 29614, 4258, 0, 4226, 23243, 54970, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 57083, 27501, 8452, 0, 4226, 25356, 2016, 
2016, 2016, 10597, 0, 0, 12678, 42260, 59196, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 63390, 46486, 14823, 0, 0, 8484, 2016, 2016, 
2016, 2016, 21130, 2145, 0, 4226, 19049, 38066, 61277, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 63390, 44373, 25356, 6339, 0, 0, 16904, 2016, 2016, 
2016, 2016, 2016, 16904, 2113, 0, 4258, 21130, 44405, 59164, 63390, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 63422, 59196, 46518, 25356, 8484, 0, 0, 10597, 29614, 2016, 2016, 
2016, 2016, 2016, 2016, 8484, 0, 0, 4258, 16904, 31695, 50712, 63390, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65503, 52857, 33840, 19017, 6371, 0, 0, 6339, 33808, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 25388, 8452, 32, 0, 32, 10597, 29614, 44373, 52825, 57051, 57083, 57083, 57083, 57083, 57051, 52857, 46518, 33840, 14791, 2145, 0, 0, 6339, 23243, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 10597, 0, 0, 0, 6339, 10597, 16936, 23275, 29582, 31695, 31695, 29582, 25356, 19017, 12678, 6339, 32, 0, 0, 8452, 29614, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 29614, 14823, 8452, 2113, 0, 0, 0, 4226, 8484, 12678, 12678, 10565, 4258, 0, 0, 0, 32, 6371, 12678, 27469, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 31727, 19017, 4258, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2145, 14823, 29582, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 25356, 16904, 10597, 8452, 6371, 6371, 6371, 6371, 8452, 10597, 14823, 23243, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
};

#endif
