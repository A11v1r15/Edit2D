/*
 * drawingTool.h
 *
 *  Created on: 5 de out de 2017
 *      Author: gilvan
 */

#ifndef INCLUDE_DRAWINGTOOL_H_
#define INCLUDE_DRAWINGTOOL_H_

#include "image2dx.h"

class DrawingTool
{
public:

	DrawingTool();

	virtual ~DrawingTool();

	virtual void reset();
	bool isMouseDown() const;

	bool onMouseDown( Image& img, int pixelX, int pixelY );
	void onMouseUp( Image& img, int pixelX, int pixelY );
	bool onMouseMove( Image& img, int pixelX, int pixelY );

	pixel getColor() const;
	void setColor(pixel color);

protected:

	virtual bool _onMouseDown( Image& img, int pixelX, int pixelY );
	virtual void _onMouseUp( Image& img, int pixelX, int pixelY );
	virtual bool _onMouseMove( Image& img, int pixelX, int pixelY );

	int downX;
	int downY;
	int lastX;
	int lastY;

	pixel color;
	bool mouseDown;
};

#endif /* INCLUDE_DRAWINGTOOL_H_ */
