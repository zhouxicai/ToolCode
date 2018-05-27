/*==========================================================================
 *  Copyright (C) 1998 Microsoft Corporation. All Rights Reserved.
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern IDirectDrawPalette * DDLoadPalette(IDirectDraw7 *pdd, LPCSTR szBitmap);
extern IDirectDrawSurface7* DDLoadBitmap(IDirectDraw7 *pdd, LPCSTR szBitmap, int dx, int dy);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface7 *pdds, LPCWSTR szBitmap);//ZXC LPCSTR->LPCWSTR
extern HRESULT              DDCopyBitmap(IDirectDrawSurface7 *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface7 *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface7 *pdds, COLORREF rgb);

#ifdef __cplusplus
}
#endif
