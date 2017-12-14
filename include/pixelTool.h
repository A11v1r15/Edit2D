/*
 * drawingTool.h
 *
 *  Created on: 5 de out de 2017
 *      Author: gilvan
 */

#ifndef INCLUDE_PIXELTOOL_H_
#define INCLUDE_PIXELTOOL_H_

#include "drawingTool.h"

class PixelTool : public DrawingTool
{
public:

	PixelTool()
		: DrawingTool()
	{
	}

	virtual ~PixelTool()
	{
	}

protected:

	virtual bool _onMouseDown( Image& img, int pixelX, int pixelY ) override
	{
		img.setPixelSafe( color,pixelX, pixelY );
		return false;
	}
	virtual void _onMouseUp( Image& img, int pixelX, int pixelY ) override
	{

	}
	virtual  bool _onMouseMove( Image& img, int pixelX, int pixelY ) override
	{
		img.setPixelSafe( color, pixelX, pixelY );
		return false;
	}
};

///
class PenTool : public DrawingTool
{
public:

	PenTool()
		: DrawingTool()
	{
	}

	virtual ~PenTool()
	{
	}

protected:

	virtual bool _onMouseDown( Image& img, int pixelX, int pixelY ) override
	{
		img.setPixelSafe( color,pixelX, pixelY );
		return true;
	}
	virtual void _onMouseUp( Image& img, int pixelX, int pixelY ) override
	{

	}
	virtual  bool _onMouseMove( Image& img, int pixelX, int pixelY ) override
	{
		img.setPixelSafe( color, pixelX, pixelY );
		return true;
	}
};


class LineTool : public DrawingTool
{
public:

	LineTool ()
		: DrawingTool ()
	{
	}

	virtual ~LineTool ()
	{
	}

protected:

	virtual bool _onMouseDown( Image& img, int pixelX, int pixelY ) override
	{
		img.lineMidPoint(color, downX, downY, pixelX, pixelY );
		return false;
	}
	virtual void _onMouseUp( Image& img, int pixelX, int pixelY ) override
	{
		img.lineMidPoint(color, downX, downY, pixelX, pixelY );
	}
	virtual  bool _onMouseMove( Image& img, int pixelX, int pixelY ) override
	{
		img.lineMidPoint(color, downX, downY, pixelX, pixelY );
		return false;
	}
};


#endif /* INCLUDE_PIXELTOOL_H_ */
