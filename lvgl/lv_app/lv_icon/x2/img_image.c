#include "img_conf.h"
#include "lv_conf.h"

#if USE_IMG_IMAGE != 0 || LV_APP_USE_INTERNAL_ICONS == 2

#include <stdint.h> 
#include "misc/others/color.h"

const color_int_t img_image [] = { /*Width = 32, Height = 27*/ 
32,	/*Width*/
27,	/*Heigth*/
16,	/*Color depth = 16*/
1,	/*Flags: Transp = 1*/
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 33808, 31727, 31727, 31727, 31727, 31727, 31727, 31727, 31727, 31727, 31727, 33808, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 29582, 19017, 14823, 12710, 12710, 14791, 14791, 14791, 14791, 14791, 14791, 12710, 12710, 14791, 16936, 27469, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 2016, 21162, 8484, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 2145, 6371, 16904, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 2016, 23243, 6339, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2113, 16936, 2016, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 2016, 2016, 2016, 25388, 10565, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6371, 25356, 2016, 2016, 2016, 2016, 2016, 
2016, 2016, 29582, 19017, 16904, 10565, 2145, 0, 0, 0, 0, 0, 32, 2145, 4258, 6339, 6339, 6339, 4226, 2113, 0, 0, 0, 0, 0, 32, 10565, 14823, 16936, 27469, 2016, 2016, 
2016, 21162, 8484, 2145, 2145, 2113, 0, 0, 0, 0, 0, 0, 6339, 12710, 23243, 27501, 27501, 25356, 16936, 8484, 0, 0, 0, 0, 0, 0, 2113, 2145, 2145, 6371, 16904, 33808, 
25356, 6339, 0, 0, 0, 0, 0, 0, 0, 0, 4226, 10597, 23243, 31727, 42260, 46518, 46518, 44373, 35953, 25388, 14791, 6339, 32, 0, 0, 0, 0, 0, 0, 0, 32, 19049, 
19017, 32, 0, 0, 0, 0, 0, 0, 0, 4226, 23243, 38066, 52825, 59196, 63390, 63422, 63422, 63390, 61277, 54938, 44405, 29582, 6371, 0, 0, 0, 0, 0, 0, 0, 0, 14791, 
14823, 0, 0, 0, 0, 0, 0, 0, 32, 14791, 40147, 57083, 65535, 65535, 65503, 63390, 61309, 63422, 65535, 65535, 63390, 46518, 19049, 4258, 32, 0, 0, 0, 0, 0, 0, 10597, 
14823, 0, 0, 0, 0, 0, 0, 2145, 12710, 31695, 54938, 65535, 65535, 63422, 50712, 42292, 42260, 48599, 61309, 65535, 65535, 57083, 40147, 21162, 4258, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 6339, 25388, 44405, 63390, 65535, 61277, 48631, 31727, 23275, 23243, 29582, 44373, 57051, 65535, 65535, 54938, 35921, 8452, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 8484, 38034, 57051, 65535, 61309, 42292, 25388, 10597, 4226, 4226, 8452, 16936, 33840, 59164, 65535, 65535, 46518, 12678, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 10597, 44405, 65503, 65535, 57083, 29614, 10565, 0, 0, 0, 0, 32, 19049, 54938, 65535, 65535, 52857, 14791, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 10597, 48599, 65535, 65535, 54970, 23243, 4226, 0, 0, 0, 0, 0, 12710, 52825, 65535, 65535, 54938, 16936, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 10597, 46518, 65535, 65535, 57051, 25388, 6371, 0, 0, 0, 0, 0, 16904, 52857, 65535, 65535, 52857, 16936, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 10565, 44373, 63390, 65535, 59196, 38034, 16936, 32, 0, 0, 0, 8452, 27501, 57051, 65535, 65535, 50744, 14791, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 8452, 33840, 52857, 65535, 65503, 50744, 33840, 16904, 6371, 6371, 12710, 27469, 42292, 61309, 65535, 63390, 44373, 10597, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 4258, 21130, 40147, 61309, 65535, 65503, 57051, 44405, 38066, 38034, 42260, 52857, 61309, 65535, 65503, 48631, 29614, 6371, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 2113, 8484, 25388, 50712, 65503, 65535, 65535, 63390, 59164, 57083, 61277, 65535, 65535, 65535, 54938, 33808, 16904, 4226, 0, 0, 0, 0, 0, 0, 12678, 
14823, 0, 0, 0, 0, 0, 0, 0, 0, 10565, 29614, 48631, 65503, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 54970, 38034, 14791, 2113, 0, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 0, 0, 2113, 14791, 29582, 46518, 57051, 59164, 59196, 61277, 59196, 57083, 50712, 35953, 21130, 2145, 0, 0, 0, 0, 0, 0, 0, 0, 12678, 
16904, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2145, 8452, 14791, 23243, 31727, 35953, 38034, 33808, 25388, 16936, 10565, 4226, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10597, 
23243, 4226, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2145, 12678, 16936, 16936, 12710, 6339, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16936, 
2016, 14823, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10565, 29582, 
2016, 33808, 14823, 6371, 6371, 8452, 8452, 8452, 8452, 8452, 8452, 8452, 6371, 6371, 6339, 6339, 6339, 6339, 6371, 6371, 8452, 8452, 8452, 8452, 8452, 8452, 8452, 6371, 6371, 14791, 27501, 2016, 
2016, 2016, 2016, 2016, 2016, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 31727, 31727, 31727, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 33808, 2016, 2016, 2016, 2016, 2016, 
};

#endif
