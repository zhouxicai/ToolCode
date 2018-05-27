//-----------------------------------------------------------------------------
// File: ddutil.cpp
//
// Desc: Routines for loading bitmap and palettes from resources
//
//
// Copyright (c) 1995-1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "ddutil.h"

HRESULT DDReLoadBitmap(IDirectDrawSurface7 *pdds, LPCWSTR szBitmap)//ZXC LPCSTR->LPCWSTR
{
    HBITMAP             hbm;
    HRESULT             hr;
	//ZXC LPCWSTR(szBitmap) Ç¿ÖÆ×ª»»
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hbm == NULL)
	hbm = (HBITMAP)LoadImage(NULL, LPCWSTR(szBitmap), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
    {
	OutputDebugString(L"handle is null\n");//ZXC
	return E_FAIL;
    }

    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
	OutputDebugString(L"ddcopybitmap failed\n");//ZXC
    }


    DeleteObject(hbm);
    return hr;
}

extern "C" HRESULT DDCopyBitmap(IDirectDrawSurface7 *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC2      ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
	return E_FAIL;

    pdds->Restore();

    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
	OutputDebugString(L"createcompatible dc failed\n");//ZXC
    HGDIOBJ oldmap=SelectObject(hdcImage, hbm);

    GetObject(hbm, sizeof(bm), &bm);
    dx = dx == 0 ? bm.bmWidth  : dx;
    dy = dy == 0 ? bm.bmHeight : dy;

    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
	StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
	pdds->ReleaseDC(hdc);
    }
	
	SelectObject(hdcImage, oldmap);
    DeleteDC(hdcImage);

    return hr;
}

extern "C" DWORD DDColorMatch(IDirectDrawSurface7 *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC2 ddsd;
    HRESULT hres;

    //
    //  use GDI SetPixel to color match for us
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
	rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
	SetPixel(hdc, 0, 0, rgb);               // set our value
	pdds->ReleaseDC(hdc);
    }

    //
    // now lock the surface so we can read back the converted color
    //
    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING);

    if (hres == DD_OK)
    {
	dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
        if(ddsd.ddpfPixelFormat.dwRGBBitCount < 32)
            dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
	pdds->Unlock(NULL);
    }

    //
    //  now put the color that was there back.
    //
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
	SetPixel(hdc, 0, 0, rgbT);
	pdds->ReleaseDC(hdc);
    }

    return dw;
}

extern "C" HRESULT DDSetColorKey(IDirectDrawSurface7 *pdds, COLORREF rgb)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}