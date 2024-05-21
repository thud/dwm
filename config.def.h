/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx              = 10;		/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating	= 0;		/* 1 means swallowing floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = {"JetBrainsMono NF:pixelsize=14",
										"monospace:size=10",
										"-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1" };
static const char dmenufont[]          = "JetBrainsMonoMedium:pixelsize=14\",\"-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1";
static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#3B4252";
static const char col_gray3[]       = "#D8DEE9";
static const char col_gray4[]       = "#ECEFF4";
static const char col_cyan[]        = "#5E81AC";
static const char col_red[]			= "#BF616A";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_red   },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "~" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	  		instance    title       	tags mask	isfloating  isterminal  noswallow	monitor */
	{ "brave-browser",	NULL,	  	NULL,			1 << 8,		0,			0,			-1,			-1 },
	{ "Alacritty",		NULL,		NULL,			0,			0,			1,			0,			-1 },
	{ "thunderbird",	NULL,		NULL,			1 << 4,		0,			0,			0,			-1 },
	{ "mpv",			NULL,		NULL,			0,			0,			0,			0,			-1 },
	{ NULL,         	NULL,		"Bluetooth",	0,  		1,			0,			0,			-1 },
	{ NULL,		  		NULL,		"Python Turtle Graphics",	0,			0,			0,			1,			-1 },
	{ NULL,		  		NULL,		"Event Tester", 0,			0,			0,			1,			-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ ]=",     tile },    /* first entry is default */
//	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, topbar ? NULL : "-b", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *termxcmd[]  = { "alacritty", "-e", "tmux", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termxcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ MODKEY,						XK_e,	   				   spawn,		   SHCMD("setbg") },
	{ MODKEY,						XK_r,	   				   spawn,		   SHCMD("screentoggle") },
	{ ControlMask,					XK_space,  				   spawn,		   SHCMD("dunstctl close") },
	{ ControlMask|ShiftMask,		XK_space,  				   spawn,		   SHCMD("dunstctl close-all") },
 	{ MODKEY,						XK_a,	   				   spawn,		   SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,				XK_a,	   				   spawn,		   SHCMD("$BROWSER --private-window --incognito") },
	{ MODKEY,       				XK_o,	   				   spawn,		   SHCMD("bt") },
	{ 0,							XF86XK_MonBrightnessDown,  spawn,		   SHCMD("xbacklight -ctrl intel_backlight -3") },
	{ 0,							XF86XK_MonBrightnessUp,	   spawn,		   SHCMD("xbacklight -ctrl intel_backlight +3") },
	{ Mod1Mask,						XF86XK_MonBrightnessDown,  spawn,		   SHCMD("xbacklight -ctrl tpacpi::kbd_backlight -10") },
	{ Mod1Mask,						XF86XK_MonBrightnessUp,	   spawn,		   SHCMD("xbacklight -ctrl tpacpi::kbd_backlight +10") },
    { 0,							XF86XK_AudioMute,   	   spawn,		   SHCMD("volume m") },
    { 0,							XF86XK_AudioRaiseVolume,   spawn,		   SHCMD("volume i") },
    { 0,							XF86XK_AudioLowerVolume,   spawn,		   SHCMD("volume d") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

