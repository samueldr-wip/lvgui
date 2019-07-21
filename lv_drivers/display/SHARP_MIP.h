/**
 * @file SHARP_MIP.h
 *
 */

#ifndef SHARP_MIP_H
#define SHARP_MIP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "../../lv_drv_conf.h"
#endif

#if USE_SHARP_MIP

#include <stdint.h>
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void sharp_mip_init(void);
void sharp_mip_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
void sharp_mip_rounder_cb(lv_disp_drv_t * disp_drv, lv_area_t * area);
void sharp_mip_set_px_cb(lv_disp_drv_t * disp_drv, uint8_t * buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);

/**********************
 *      MACROS
 **********************/

#endif /* USE_SHARP_MIP */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SHARP_MIP_H */
