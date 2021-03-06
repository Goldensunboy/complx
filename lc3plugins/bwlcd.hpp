#ifndef BWLCD_HPP
#define BWLCD_HPP

#include <lc3_plugin.hpp>
#include <lc3_parser.hpp>
#include <wx/wx.h>
#include "BWLCDGUI.h"

#define BWLCD_MAJOR_VERSION 1
#define BWLCD_MINOR_VERSION 3

#define TILE_SIZE 10
#define MIN_SIZE 100

wxDECLARE_EVENT(wxEVT_COMMAND_CREATE_DISPLAY, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_DESTROY_DISPLAY, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_UPDATE_DISPLAY, wxThreadEvent);

class BWLCD : public BWLCDGUI
{
    public:
        BWLCD(wxWindow* top, int width, int height, unsigned short startaddr, unsigned int off, unsigned int on, unsigned int maxsize);
        ~BWLCD();
		virtual void OnUpdate(wxThreadEvent& event);
		void OnPaint( wxPaintEvent& event );
	int width;
	int height;
    private:
        lc3_state* state;
        unsigned short startaddr;
        unsigned int off;
        unsigned int on;
	unsigned int maxsize;
};

class BWLCDPlugin : public wxEvtHandler, public Plugin
{
    public:
        BWLCDPlugin(unsigned short widthaddr, unsigned short heightaddr, unsigned short initaddr, unsigned short startaddr, unsigned int offcolor = 0xa0b0a0, unsigned int oncolor = 0x606860, unsigned int maxsize = 500);
        ~BWLCDPlugin();
        virtual void OnMemoryWrite(lc3_state& state, unsigned short address, short value);
        //virtual void OnTock(lc3_state& state);
        void InitDisplay(wxThreadEvent& event);
        void UpdateDisplay(wxThreadEvent& event);
        void DestroyDisplay(wxThreadEvent& event);
    private:
        unsigned short width;
	unsigned short height;
        unsigned short widthaddr;
        unsigned short heightaddr;
        unsigned short initaddr;
        unsigned short startaddr;
        unsigned int offcolor;
        unsigned int oncolor;
	unsigned int maxsize;
        BWLCD* lcd;
        bool lcd_initializing;

};

extern "C" Plugin* create_plugin(const std::map<std::string, std::string>& params);
extern "C" void destroy_plugin(Plugin* ptr);

#endif

