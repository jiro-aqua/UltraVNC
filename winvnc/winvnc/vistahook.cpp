
#include "vncDesktopThread.h"
int g_Oldcounter=0;

inline bool
ClipRect(int *x, int *y, int *w, int *h,
	    int cx, int cy, int cw, int ch) {
  if (*x < cx) {
    *w -= (cx-*x);
    *x = cx;
  }
  if (*y < cy) {
    *h -= (cy-*y);
    *y = cy;
  }
  if (*x+*w > cx+cw) {
    *w = (cx+cw)-*x;
  }
  if (*y+*h > cy+ch) {
    *h = (cy+ch)-*y;
  }
  return (*w>0) && (*h>0);
}

bool
vncDesktopThread::Handle_Ringbuffer(mystruct *ringbuffer,rfb::Region2D &rgncache)
{
	vnclog.Print(LL_INTERR, VNCLOG("counter,g_Oldcounter %i %i  \n"),ringbuffer->counter,g_Oldcounter);
	if (ringbuffer->counter==g_Oldcounter) return 0;
	int counter=ringbuffer->counter;
	if (counter<1 || counter>1999) return 0;

	if (g_Oldcounter<counter)
	{
		for (ULONG i =g_Oldcounter+1; i<=counter;i++)
		{
			if (ringbuffer->type[i]==0)
			{
				rfb::Rect rect;
				rect.tl = rfb::Point(ringbuffer->rect1[i].left, ringbuffer->rect1[i].top);
				rect.br = rfb::Point(ringbuffer->rect1[i].right, ringbuffer->rect1[i].bottom);
				//Buffer coordinates
				rect.tl.x-=m_desktop->m_ScreenOffsetx;
				rect.br.x-=m_desktop->m_ScreenOffsetx;
				rect.tl.y-=m_desktop->m_ScreenOffsety;
				rect.br.y-=m_desktop->m_ScreenOffsety;
				//vnclog.Print(LL_INTERR, VNCLOG("REct %i %i %i %i  \n"),rect.tl.x,rect.br.x,rect.tl.y,rect.br.y);
				
				rect = rect.intersect(m_desktop->m_Cliprect);
				if (!rect.is_empty())
				{
					rgncache = rgncache.union_(rect);
				}
			}
			if (ringbuffer->type[i]==2 || ringbuffer->type[i]==4)
			{
				if (MyGetCursorInfo)
					{
						MyCURSORINFO cinfo;
						cinfo.cbSize=sizeof(MyCURSORINFO);
						MyGetCursorInfo(&cinfo);
						m_desktop->SetCursor(cinfo.hCursor);
						//vnclog.Print(LL_INTERR, VNCLOG("Cursor %i  \n"),cinfo.hCursor);
					}
	
				
			}
			
		}

	}
	else
	{
		ULONG i = 0;
		for (i =g_Oldcounter+1;i<2000;i++)
		{
			if (ringbuffer->type[i]==0 )
			{
				rfb::Rect rect;
				rect.tl = rfb::Point(ringbuffer->rect1[i].left, ringbuffer->rect1[i].top);
				rect.br = rfb::Point(ringbuffer->rect1[i].right, ringbuffer->rect1[i].bottom);
				//Buffer coordinates
				rect.tl.x-=m_desktop->m_ScreenOffsetx;
				rect.br.x-=m_desktop->m_ScreenOffsetx;
				rect.tl.y-=m_desktop->m_ScreenOffsety;
				rect.br.y-=m_desktop->m_ScreenOffsety;
				//vnclog.Print(LL_INTERR, VNCLOG("REct %i %i %i %i  \n"),rect.tl.x,rect.br.x,rect.tl.y,rect.br.y);
				
				rect = rect.intersect(m_desktop->m_Cliprect);
				if (!rect.is_empty())
				{
					rgncache = rgncache.union_(rect);
				}
			}
			if (ringbuffer->type[i]==2 || ringbuffer->type[i]==4)
			{
				if (MyGetCursorInfo)
					{
						MyCURSORINFO cinfo;
						cinfo.cbSize=sizeof(MyCURSORINFO);
						MyGetCursorInfo(&cinfo);
						m_desktop->SetCursor(cinfo.hCursor);
						//vnclog.Print(LL_INTERR, VNCLOG("Cursor %i  \n"),cinfo.hCursor);
					}
				
			}
			
		}
		for (i=1;i<=counter;i++)
		{
			if (ringbuffer->type[i]==0 )
			{
				rfb::Rect rect;
				rect.tl = rfb::Point(ringbuffer->rect1[i].left, ringbuffer->rect1[i].top);
				rect.br = rfb::Point(ringbuffer->rect1[i].right, ringbuffer->rect1[i].bottom);
				//Buffer coordinates
				rect.tl.x-=m_desktop->m_ScreenOffsetx;
				rect.br.x-=m_desktop->m_ScreenOffsetx;
				rect.tl.y-=m_desktop->m_ScreenOffsety;
				rect.br.y-=m_desktop->m_ScreenOffsety;
				//vnclog.Print(LL_INTERR, VNCLOG("REct %i %i %i %i  \n"),rect.tl.x,rect.br.x,rect.tl.y,rect.br.y);
				
				rect = rect.intersect(m_desktop->m_Cliprect);
				if (!rect.is_empty())
				{
					rgncache = rgncache.union_(rect);
				}
			}
			if (ringbuffer->type[i]==2 || ringbuffer->type[i]==4)
			{
				if (MyGetCursorInfo)
					{
						MyCURSORINFO cinfo;
						cinfo.cbSize=sizeof(MyCURSORINFO);
						MyGetCursorInfo(&cinfo);
						m_desktop->SetCursor(cinfo.hCursor);
						//vnclog.Print(LL_INTERR, VNCLOG("Cursor %i  \n"),cinfo.hCursor);
					}
				
			}
			
		}
	}
	g_Oldcounter=counter;
	return 1;
}