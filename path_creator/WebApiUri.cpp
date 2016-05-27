/**
 * Sony CONFIDENTIAL
 * Copyright (C) 2015 Sony Corporation, All Rights Reserved.
 * @file   $File: //depot/UNI-SYSTEM-RE/BASELINE/NetService/Common/WebApiUri.cpp $
 * @brief  
 * @author 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "WebApiUri.h"
#include "WebApiDebug.h"

 /*-----------------------------------------------------------
  Macro
 -----------------------------------------------------------*/
#define NUM_OF_TABLE(table)		(sizeof(table) / sizeof(table[0]))
#define STR_CMP					strncasecmp

 /*-----------------------------------------------------------
  Internal Define
 -----------------------------------------------------------*/
#define URI_STR_INVALID				"invalid"
#define URI_STR_TV					"tv"
#define URI_STR_EXTINPUT			"extInput"
#define URI_STR_VIDEO				"video"
#define URI_STR_AUDIO				"audio"
#define URI_STR_STORAGE				"storage"
#define URI_STR_HOUSEMOVING			"housemoving"

#define URI_STR_ISDBT				"isdbt"
#define URI_STR_ISDBBS				"isdbbs"
#define URI_STR_ISDBCS				"isdbcs"
#define URI_STR_CONTENT				"content"
#define URI_STR_BD					"bd"
#define URI_STR_DVD					"dvd"
#define URI_STR_USB1				"usb1"
#define URI_STR_USB2				"usb2"
#define URI_STR_INTERNAL_HDD		"internalHdd"
#define URI_STR_CD					"cd"
#define URI_STR_ALL					"all"
#define URI_STR_MOVIE				"movie"

#define URI_STR_TRIP				"trip"
#define URI_STR_CONTENT_ID			"contentId"
#define URI_STR_STORAGE_TYPE		"storageType"
#define URI_STR_TITLE_TYPE			"titleType"
#define URI_STR_STREAM_TYPE			"streamType"
#define URI_STR_FOLDER_TYPE			"folderType"
#define URI_STR_TITLE_NO			"titleNo"
#define URI_STR_INDEX				"index"
#define URI_STR_UUID				"uuid"

// path
#define URI_STR_ASTERISK			"*"
#define URI_STR_PATH				"path"
#define URI_STR_PATH_TITLE			"/title/"
#define URI_STR_PATH_RECORDINGTYPE	"/recordingType/"
#define URI_STR_PATH_ALBUM			"/album/"
#define URI_STR_PATH_ARTIST			"/artist/"

// usbDeviceType
#define URI_STR_USB_DEVICE_TYPE		"usbDeviceType"
#define URI_STR_EXTERNAL_DEVICE		"externalDevice"

// titleType
#define URI_STR_TITLE_NONE			"none"
#define URI_STR_TITLE_UNKNOWN		"unknown"
#define URI_STR_TITLE_ORIGINAL		"original"
#define URI_STR_TITLE_PLAYLIST		"playlist"
#define URI_STR_TITLE_TOPMENU		"topMenu"
#define URI_STR_TITLE_MENU			"menu"
#define URI_STR_TITLE_AUTOPLAY		"autoPlay"
#define URI_STR_TITLE_FREEORG		"freeOrg"
#define URI_STR_TITLE_FREEPL		"freePl"
#define URI_STR_TITLE_FREE			"free"
#define URI_STR_TITLE_BDREAL		"bdReal"
#define URI_STR_TITLE_BDVIRTUAL		"bdVirtual"
#define URI_STR_TITLE_ACTV			"actv"
#define URI_STR_TITLE_PICORIGINAL	"picOriginal"
#define URI_STR_TITLE_PICLARGE		"picLarge"
#define URI_STR_TITLE_PICMIDDLE		"picMiddle"
#define URI_STR_TITLE_PICSMALL		"picSmall"
#define URI_STR_TITLE_PICTHUMB		"picThumb"
#define URI_STR_TITLE_FOLDER		"folder"
#define URI_STR_TITLE_XPICSTORY		"xpicStory"
#define URI_STR_TITLE_XSCRAPBOOK	"xscrapBook"
#define URI_STR_TITLE_STILLALL		"stillAll"
#define URI_STR_TITLE_BGM			"bgm"
#define URI_STR_TITLE_MUSIC			"music"
#define URI_STR_TITLE_AVCHD			"avchd"
#define URI_STR_TITLE_ONETOUCHDISC	"oneTouchDisc"
#define URI_STR_TITLE_AVCHDALL		"avchdAll"
#define URI_STR_TITLE_AVCHDDIFF		"avchdDiff"
#define URI_STR_TITLE_AVCHDALLDISC	"avchdAllDisc"
#define URI_STR_TITLE_AVCHDDIFFDISC	"avchdDiffDisc"
#define URI_STR_TITLE_INVALID		"invalid"
#define URI_STR_TITLE_NOTVISIBLE	"notVisible"
#define URI_STR_TITLE_SAMPLE		"sample"
#define URI_STR_TITLE_KLEIOODEKAKE	"kleioOdekake"
#define URI_STR_TITLE_MP4			"mp4"
#define URI_STR_TITLE_MP4_4K		"mp44k"

// streamType
#define URI_STR_STREAM_UNKNOWN		"unknown"
#define URI_STR_STREAM_PS			"ps"
#define URI_STR_STREAM_TS			"ts"
#define URI_STR_STREAM_SOUND		"sound"
#define URI_STR_STREAM_PICTURE		"picture"
#define URI_STR_STREAM_FOLDER		"folder"
#define URI_STR_STREAM_IMAGE		"image"
#define URI_STR_STREAM_BGM			"bgm"
#define URI_STR_STREAM_AVC			"avc"
#define URI_STR_STREAM_SCRAP		"scrap"
#define URI_STR_STREAM_AVCHD		"avchd"

// folderType
#define URI_STR_FOLDER_UNKNOWN			"unknown"
#define URI_STR_FOLDER_ROOT				"root"
#define URI_STR_FOLDER_VIDEO_ROOT		"video_root"
#define URI_STR_FOLDER_ALBUM			"album"
#define URI_STR_FOLDER_ROOT_XPIC		"root_xpic"
#define URI_STR_FOLDER_ROOT_SAMPLE		"root_sample"
#define URI_STR_FOLDER_DVDMENU			"dvdmenu"
#define URI_STR_FOLDER_SAMPLE_ALBUM		"sample_album"
#define URI_STR_FOLDER_ROOT_XSCRAP		"root_xscrap"
#define URI_STR_FOLDER_XPIC_THUM		"xpic_thum"
#define URI_STR_FOLDER_XSCRAP_THUM		"xscrap_thum"
#define URI_STR_FOLDER_XPIC_EFFECT		"xpic_effect"
#define URI_STR_FOLDER_XSCRAP_TEMP		"xscrap_temp"
#define URI_STR_FOLDER_XSCRAP_THEME		"xscrap_theme"
#define URI_STR_FOLDER_ROOT_FREE_AREA	"root_free_area"
#define URI_STR_FOLDER_BDJMENU			"bdjmenu"

 /*-----------------------------------------------------------
  Static Table
 -----------------------------------------------------------*/
// SchemeKey Table
struct SCHEME_KEY_TABLE
{
	WEBAPI_URI_SCHEME_KEY	key;
	const char*				str;
};
static const SCHEME_KEY_TABLE s_schemeKeyTable[] = {
	{ SCHEME_KEY_INVALID, URI_STR_INVALID },
	{ SCHEME_KEY_TV, URI_STR_TV },
	{ SCHEME_KEY_EXT, URI_STR_EXTINPUT },
	{ SCHEME_KEY_VIDEO, URI_STR_VIDEO },
	{ SCHEME_KEY_AUDIO, URI_STR_AUDIO },
	{ SCHEME_KEY_STORAGE, URI_STR_STORAGE },
	{ SCHEME_KEY_HOUSEMOVING, URI_STR_HOUSEMOVING},
};
static const int s_schemeKeyNum = NUM_OF_TABLE(s_schemeKeyTable);
// SchemeValue Table
struct SCHEME_VALUE_TABLE
{
	WEBAPI_URI_SCHEME_VAL	value;
	const char*				str;
};
static const SCHEME_VALUE_TABLE s_schemeValueTable[] = {
	{ SCHEME_VAL_INVALID, URI_STR_INVALID },
	{ SCHEME_VAL_ISDBT, URI_STR_ISDBT },
	{ SCHEME_VAL_ISDBBS, URI_STR_ISDBBS },
	{ SCHEME_VAL_ISDBCS, URI_STR_ISDBCS },
	{ SCHEME_VAL_VIDEO, URI_STR_VIDEO },
	{ SCHEME_VAL_CONTENT, URI_STR_CONTENT },
	{ SCHEME_VAL_INTERNAL_HDD, URI_STR_INTERNAL_HDD },
	{ SCHEME_VAL_BD, URI_STR_BD },
	{ SCHEME_VAL_DVD, URI_STR_DVD },
	{ SCHEME_VAL_CD, URI_STR_CD },
	{ SCHEME_VAL_USB1, URI_STR_USB1 },
	{ SCHEME_VAL_USB2, URI_STR_USB2 },
	{ SCHEME_VAL_ALL, URI_STR_ALL },
	{ SCHEME_VAL_ASTERISK, URI_STR_ASTERISK },
	{ SCHEME_VAL_MOVIE, URI_STR_MOVIE },
};
static const int s_schemeValueNum = NUM_OF_TABLE(s_schemeValueTable);
// ParamType Table
struct PARAM_TYPE_TABLE
{
	WEBAPI_URI_PARAM_TYPE	type;
	const char*				str;
};
static const PARAM_TYPE_TABLE s_paramTypeTable[] = {
	{ PARAM_TYPE_INVALID, URI_STR_INVALID },
	{ PARAM_TYPE_TRIPLET, URI_STR_TRIP },
	{ PARAM_TYPE_CONTENT_ID, URI_STR_CONTENT_ID },
	{ PARAM_TYPE_STORAGE_TYPE, URI_STR_STORAGE_TYPE },
	{ PARAM_TYPE_TITLE_TYPE, URI_STR_TITLE_TYPE },
	{ PARAM_TYPE_STREAM_TYPE, URI_STR_STREAM_TYPE },
	{ PARAM_TYPE_FOLDER_TYPE, URI_STR_FOLDER_TYPE },
	{ PARAM_TYPE_TITLE_NO, URI_STR_TITLE_NO },
	{ PARAM_TYPE_INDEX, URI_STR_INDEX },
	{ PARAM_TYPE_PATH, URI_STR_PATH },
	{ PARAM_TYPE_USB_DEVICE_TYPE, URI_STR_USB_DEVICE_TYPE },
	{ PARAM_TYPE_UUID, URI_STR_UUID },
};
static const int s_paramTypeNum = NUM_OF_TABLE(s_paramTypeTable);
// StorageType Table
struct STORAGE_TYPE_TABLE
{
	WEBAPI_URI_STORAGE_TYPE	type;
	const char*				str;
};
static const STORAGE_TYPE_TABLE s_storageTypeTable[] = {
	{ STORAGE_TYPE_INVALID, URI_STR_INVALID },
	{ STORAGE_TYPE_INTERNAL_HDD, URI_STR_INTERNAL_HDD },
	{ STORAGE_TYPE_BD, URI_STR_BD },
	{ STORAGE_TYPE_DVD, URI_STR_DVD },
	{ STORAGE_TYPE_CD, URI_STR_CD },
	{ STORAGE_TYPE_USB1, URI_STR_USB1 },
	{ STORAGE_TYPE_USB2, URI_STR_USB2 },
	{ STORAGE_TYPE_ALL, URI_STR_ALL },
};
static const int s_storageTypeNum = NUM_OF_TABLE(s_storageTypeTable);
// TitleType Table
struct TITLE_TYPE_TABLE
{
	WEBAPI_URI_TITLE_TYPE	webapi_type;
	const char*				str;
	TTL_TYPE 				ttl_type;
};
static const TITLE_TYPE_TABLE s_titleTypeTable[] = {
	{ TITLE_TYPE_NONE, URI_STR_TITLE_NONE, TTL_TYPE_NONE },
	{ TITLE_TYPE_UNKNOWN, URI_STR_TITLE_UNKNOWN, TTL_TYPE_UNKNOWN },
	{ TITLE_TYPE_ORIGINAL, URI_STR_TITLE_ORIGINAL, TTL_TYPE_ORIGINAL },
	{ TITLE_TYPE_PLAYLIST, URI_STR_TITLE_PLAYLIST, TTL_TYPE_PLAYLIST },
	{ TITLE_TYPE_TOPMENU, URI_STR_TITLE_TOPMENU, TTL_TYPE_TOP_MENU },
	{ TITLE_TYPE_MENU, URI_STR_TITLE_MENU, TTL_TYPE_MENU },
	{ TITLE_TYPE_AUTOPLAY, URI_STR_TITLE_AUTOPLAY, TTL_TYPE_AUTO_PLAY },
	{ TITLE_TYPE_FREEORG, URI_STR_TITLE_FREEORG, TTL_TYPE_FREE_ORG },
	{ TITLE_TYPE_FREEPL, URI_STR_TITLE_FREEPL, TTL_TYPE_FREE_PL },
	{ TITLE_TYPE_FREE, URI_STR_TITLE_FREE, TTL_TYPE_FREE },
	{ TITLE_TYPE_BDREAL, URI_STR_TITLE_BDREAL, TTL_TYPE_BD_REAL },
	{ TITLE_TYPE_BDVIRTUAL, URI_STR_TITLE_BDVIRTUAL, TTL_TYPE_BD_VIRTUAL },
	{ TITLE_TYPE_ACTV, URI_STR_TITLE_ACTV, TTL_TYPE_ACTV },
	{ TITLE_TYPE_PICORIGINAL, URI_STR_TITLE_PICORIGINAL, TTL_TYPE_PIC_ORIGINAL },
	{ TITLE_TYPE_PICLARGE, URI_STR_TITLE_PICLARGE, TTL_TYPE_PIC_LARGE },
	{ TITLE_TYPE_PICMIDDLE, URI_STR_TITLE_PICMIDDLE, TTL_TYPE_PIC_MIDDLE },
	{ TITLE_TYPE_PICSMALL, URI_STR_TITLE_PICSMALL, TTL_TYPE_PIC_SMALL },
	{ TITLE_TYPE_PICTHUMB, URI_STR_TITLE_PICTHUMB, TTL_TYPE_PIC_THUMB },
	{ TITLE_TYPE_FOLDER, URI_STR_TITLE_FOLDER, TTL_TYPE_FOLDER },
	{ TITLE_TYPE_XPICSTORY, URI_STR_TITLE_XPICSTORY, TTL_TYPE_XPIC_STORY },
	{ TITLE_TYPE_XSCRAPBOOK, URI_STR_TITLE_XSCRAPBOOK, TTL_TYPE_XSCRAP_BOOK },
	{ TITLE_TYPE_STILLALL, URI_STR_TITLE_STILLALL, TTL_TYPE_STILL_ALL },
	{ TITLE_TYPE_BGM, URI_STR_TITLE_BGM, TTL_TYPE_BGM },
	{ TITLE_TYPE_MUSIC, URI_STR_TITLE_MUSIC, TTL_TYPE_MUSIC },
	{ TITLE_TYPE_AVCHD, URI_STR_TITLE_AVCHD, TTL_TYPE_AVCHD },
	{ TITLE_TYPE_ONETOUCHDISC, URI_STR_TITLE_ONETOUCHDISC, TTL_TYPE_ONE_TOUCH_DISC },
	{ TITLE_TYPE_AVCHDALL, URI_STR_TITLE_AVCHDALL, TTL_TYPE_AVCHD_ALL },
	{ TITLE_TYPE_AVCHDDIFF, URI_STR_TITLE_AVCHDDIFF, TTL_TYPE_AVCHD_DIFF },
	{ TITLE_TYPE_AVCHDALLDISC, URI_STR_TITLE_AVCHDALLDISC, TTL_TYPE_AVCHD_ALL_DISC },
	{ TITLE_TYPE_AVCHDDIFFDISC, URI_STR_TITLE_AVCHDDIFFDISC, TTL_TYPE_AVCHD_DIFF_DISC },
	{ TITLE_TYPE_INVALID, URI_STR_TITLE_INVALID, TTL_TYPE_INVALID },
	{ TITLE_TYPE_NOTVISIBLE, URI_STR_TITLE_NOTVISIBLE, TTL_TYPE_NOT_VISIBLE },
	{ TITLE_TYPE_SAMPLE, URI_STR_TITLE_SAMPLE, TTL_TYPE_SAMPLE },
	{ TITLE_TYPE_KLEIOODEKAKE, URI_STR_TITLE_KLEIOODEKAKE, TTL_TYPE_KLEIO_ODEKAKE },
	// { TITLE_TYPE_MP4, URI_STR_TITLE_MP4, TTL_TYPE_MP4 },
	// { TITLE_TYPE_MP4_4K, URI_STR_TITLE_MP4_4K, TTL_TYPE_MP4_4K },
};
static const int s_titleTypeNum = NUM_OF_TABLE(s_titleTypeTable);
// StreamType Table
struct STREAM_TYPE_TABLE
{
	WEBAPI_URI_STREAM_TYPE	webapi_type;
	const char*				str;
	TTL_STRM 				stream_type;
};
static const STREAM_TYPE_TABLE s_streamTypeTable[] = {
	{ STREAM_TYPE_UNKNOWN, URI_STR_STREAM_UNKNOWN, TTL_UNKNOWN_STRM },
	{ STREAM_TYPE_PS, URI_STR_STREAM_PS, TTL_PS_STRM },
	{ STREAM_TYPE_TS, URI_STR_STREAM_TS, TTL_TS_STRM },
	{ STREAM_TYPE_SOUND, URI_STR_STREAM_SOUND, TTL_SOUND },
	{ STREAM_TYPE_PICTURE, URI_STR_STREAM_PICTURE, TTL_PICTURE },
	{ STREAM_TYPE_FOLDER, URI_STR_STREAM_FOLDER, TTL_FOLDER },
	{ STREAM_TYPE_IMAGE, URI_STR_STREAM_IMAGE, TTL_IMAGE },
	{ STREAM_TYPE_BGM, URI_STR_STREAM_BGM, TTL_BGM },
	{ STREAM_TYPE_AVC, URI_STR_STREAM_AVC, TTL_AVC_STRM },
	{ STREAM_TYPE_SCRAP, URI_STR_STREAM_SCRAP, TTL_SCRAP_STRM },
	{ STREAM_TYPE_AVCHD, URI_STR_STREAM_AVCHD, TTL_AVCHD_STRM },
};
static const int s_streamTypeNum = NUM_OF_TABLE(s_streamTypeTable);
// FolderType Table
struct FOLDER_TYPE_TABLE
{
	WEBAPI_URI_FOLDER_TYPE	webapi_type;
	const char*				str;
	Ushort					folder_type;
};
static const FOLDER_TYPE_TABLE s_folderTypeTable[] = {
	{ FOLDER_TYPE_UNKNOWN, URI_STR_FOLDER_UNKNOWN, TTL_UNKNOWN_FOLDER },
	{ FOLDER_TYPE_ROOT, URI_STR_FOLDER_ROOT, TTL_ROOT_FOLDER },
	{ FOLDER_TYPE_VIDEO_ROOT, URI_STR_FOLDER_VIDEO_ROOT, TTL_VIDEO_ROOT_FOLDER },
	{ FOLDER_TYPE_ALBUM, URI_STR_FOLDER_ALBUM, TTL_ALBUM_FOLDER },
	{ FOLDER_TYPE_ROOT_XPIC, URI_STR_FOLDER_ROOT_XPIC, TTL_ROOT_XPIC_FOLDER },
	{ FOLDER_TYPE_ROOT_SAMPLE, URI_STR_FOLDER_ROOT_SAMPLE, TTL_ROOT_SAMPLE_FOLDER },
	{ FOLDER_TYPE_DVDMENU, URI_STR_FOLDER_DVDMENU, TTL_DVDMENU_FOLDER },
	{ FOLDER_TYPE_SAMPLE_ALBUM, URI_STR_FOLDER_SAMPLE_ALBUM, TTL_SAMPLE_ALBUM_FOLDER },
	{ FOLDER_TYPE_ROOT_XSCRAP, URI_STR_FOLDER_ROOT_XSCRAP, TTL_ROOT_XSCRAP_FOLDER },
	{ FOLDER_TYPE_XPIC_THUM, URI_STR_FOLDER_XPIC_THUM, TTL_XPIC_THUM_FOLDER },
	{ FOLDER_TYPE_XSCRAP_THUM, URI_STR_FOLDER_XSCRAP_THUM, TTL_XSCRAP_THUM_FOLDER },
	{ FOLDER_TYPE_XPIC_EFFECT, URI_STR_FOLDER_XPIC_EFFECT, TTL_XPIC_EFFECT_FOLDER },
	{ FOLDER_TYPE_XSCRAP_TEMP, URI_STR_FOLDER_XSCRAP_TEMP, TTL_XSCRAP_TEMP_FOLDER },
	{ FOLDER_TYPE_XSCRAP_THEME, URI_STR_FOLDER_XSCRAP_THEME, TTL_XSCRAP_THEME_FOLDER },
	{ FOLDER_TYPE_ROOT_FREE_AREA, URI_STR_FOLDER_ROOT_FREE_AREA, TTL_ROOT_FREE_AREA_FOLDER },
	{ FOLDER_TYPE_BDJMENU, URI_STR_FOLDER_BDJMENU, TTL_BDJMENU_FOLDER },
};
static const int s_folderTypeNum = NUM_OF_TABLE(s_folderTypeTable);

// InputType Table
struct INPUT_TYPE_TABLE
{
	EN_FD_INPUT_TYPE			type;
	WEBAPI_URI_SCHEME_VAL		scheme;
	const char*					str;
};
static const INPUT_TYPE_TABLE s_inputTypeTable[] = {
	{ FD_INPUT_TYPE_INVALID, SCHEME_VAL_INVALID, URI_STR_INVALID },
	{ FD_INPUT_TYPE_TRD, SCHEME_VAL_ISDBT, URI_STR_ISDBT },
	{ FD_INPUT_TYPE_BSD, SCHEME_VAL_ISDBBS, URI_STR_ISDBBS },
	{ FD_INPUT_TYPE_CSD, SCHEME_VAL_ISDBCS, URI_STR_ISDBCS },
	// { FD_INPUT_TYPE_LINE, SCHEME_VAL_VIDEO, URI_STR_VIDEO },
};
static const int s_inputTypeNum = NUM_OF_TABLE(s_inputTypeTable);

// CasType Table
struct CAS_TYPE_TABLE
{
	EN_FD_CAS_TYPE			type;
	WEBAPI_URI_SCHEME_VAL		scheme;
	const char*					str;
};
static const CAS_TYPE_TABLE s_casTypeTable[] = {
	{ FD_CAS_NULL, SCHEME_VAL_INVALID, URI_STR_INVALID },
	{ FD_CAS_TRD, SCHEME_VAL_ISDBT, URI_STR_ISDBT },
	{ FD_CAS_BSD, SCHEME_VAL_ISDBBS, URI_STR_ISDBBS },
	{ FD_CAS_CSD, SCHEME_VAL_ISDBCS, URI_STR_ISDBCS },
	{ FD_CAS_SKP, SCHEME_VAL_INVALID, URI_STR_INVALID },
	{ FD_CAS_HDD, SCHEME_VAL_STORAGE, URI_STR_STORAGE },
};
static const int s_casTypeNum = NUM_OF_TABLE(s_casTypeTable);

/*-----------------------------------------------------------
  Common
 -----------------------------------------------------------*/
static bool _isEqual(const char* str1, const char* str2)
{
	if (STR_CMP(str1, str2, WEBAPI_URI_STRING_MAX) == 0) {
		return true;
	}
	else {
		return false;
	}
}

static bool _isMatch(const char* str1, const char* str2)
{
	if (STR_CMP(str1, str2, strlen(str2)) == 0) {
		return true;
	}
	else {
		return false;
	}
}

/*-----------------------------------------------------------
  CWebApiUriParser
 -----------------------------------------------------------*/
CWebApiUriParser::CWebApiUriParser(const char* uri)
{
	WA_TRACE();
	init();
	if (uri == NULL) {
		WA_WARN("uri is NULL\n");
		return;
	}
	m_len = strlen(uri);
	if (m_len > WEBAPI_URI_STRING_MAX) {
		WA_ERROR("uri length orver(%d)\n", m_len);
		return;
	}
	strncpy(m_uri, uri, WEBAPI_URI_STRING_MAX);
	/*toLower();*/
	WA_DEBUG("Uri[%s](%d)\n", m_uri,m_len);

	int ret = parse();
	if (ret == 0) {
		m_isValid = true;
	}
}

CWebApiUriParser::CWebApiUriParser(const char* uri, const char* type)
{
	WA_TRACE();
	init();
	if (uri == NULL) {
		WA_WARN("uri is NULL\n");
		return;
	}
	m_len = strlen(uri);
	if (m_len > WEBAPI_URI_STRING_MAX) {
		WA_ERROR("uri length orver(%d)\n", m_len);
		return;
	}
	strncpy(m_uri, uri, WEBAPI_URI_STRING_MAX);
	/*toLower();*/
	WA_DEBUG("Uri[%s](%d)\n", m_uri,m_len);

	setType(type);

	int ret = parse();
	if (ret == 0) {
		m_isValid = true;
	}
}

void CWebApiUriParser::setType(const char* type)
{
	if (type == NULL) {
		m_type = URI_TYPE_NONE;
		return;
	}

	WA_DEBUG("Type[%s]\n", type);
	if (isEqual(type, "movie")) {
		m_type = URI_TYPE_MOVIE;
	}
	else if (isEqual(type, "movie_avchd")) {
		m_type = URI_TYPE_MOVIE_AVCHD;
	}
	else if (isEqual(type, "movie_mp4")) {
		m_type = URI_TYPE_MOVIE_MP4;
	}
	else if (isEqual(type, "music")) {
		m_type = URI_TYPE_MUSIC;
	}
	else {
		m_type = URI_TYPE_NONE;
	}
}

bool CWebApiUriParser::isTypeOf(WEBAPI_URI_TYPE type)
{
	if (type == m_type) {
		return true;
	}
	else {
		return false;
	}
}

CWebApiUriParser::~CWebApiUriParser()
{
}

// Base
int CWebApiUriParser::parse()
{
	int ret = 0;
	char* pos = NULL;

	// Scheme
	pos = strtok(m_uri, ":");
	if (pos == NULL) {
		WA_WARN("SchemeKey is NULL\n");
		return -1;
	}
	ret = parseSchemeKey(pos);
	if (ret != 0) {
		WA_ERROR("parseScheme Error[%s]\n", pos);
		return ret;
	}
	pos = strtok(NULL, "?");
	if (pos == NULL) {
		WA_ERROR("SchemeValue is NULL\n");
		return -1;
	}
	ret = parseSchemeValue(pos);
	if (ret != 0) {
		WA_ERROR("parseScheme Error[%s]\n", pos);
		return ret;
	}

	// param
	int paramIndex = 0;
	while ((pos = strtok(NULL, "&")) != NULL) {
		ret = parseParam(pos, paramIndex);
		if (ret != 0) {
			WA_ERROR("parseScheme Error[%s]\n", pos);
			return ret;
		}
		paramIndex++;
	}

	return ret;
}

int CWebApiUriParser::parseSchemeKey(const char* str)
{
	for (int i = 0; i < s_schemeKeyNum; i++) {
		if (isEqual(str, s_schemeKeyTable[i].str)) {
			m_schemeKey = s_schemeKeyTable[i].key;
			return 0;
		}
	}
	m_schemeKey = SCHEME_KEY_INVALID;
	return -1;
}

int CWebApiUriParser::parseSchemeValue(const char* str)
{
	for (int i = 0; i < s_schemeValueNum; i++) {
		if (isEqual(str, s_schemeValueTable[i].str)) {
			m_schemeVal = s_schemeValueTable[i].value;
			return 0;
		}
	}
	m_schemeVal = SCHEME_VAL_INVALID;
	return -1;
}

int CWebApiUriParser::parseParam(const char* str, int paramIndex)
{
	char tempParam[WEBAPI_URI_STRING_MAX+1] = {};
	strncpy(tempParam, str, WEBAPI_URI_STRING_MAX);

	WA_DEBUG("param[%s]\n", tempParam);
	if (paramIndex >= WEBAPI_URI_PARAM_REGIST_MAX) {
		WA_ERROR("Param num Error(%d)\n", paramIndex);
		return -1;
	}

	// matching
	for (int i = 0; i < s_paramTypeNum; i++) {
		if (isMatch(tempParam, s_paramTypeTable[i].str)) {
			setParam(s_paramTypeTable[i].type, tempParam, m_param[paramIndex]);
			return 0;
		}
	}
	WA_ERROR("Param type Error(%s)\n", tempParam);
	return -1;
}

void CWebApiUriParser::setParam(WEBAPI_URI_PARAM_TYPE type, char* str, ParamType& param)
{
	param.paramType = type;
	WA_DEBUG("paramType=%d\n", param.paramType);
	char* pos = strchr(str, '=');
	if (pos == NULL) {
		WA_ERROR("paramValue is none\n");
	}
	strncpy(param.paramValue, pos + 1, WEBAPI_URI_PARAM_VALUE_MAX);
	WA_DEBUG("paramValue=%s\n", param.paramValue);
}

const char* CWebApiUriParser::getParamValue(WEBAPI_URI_PARAM_TYPE paramType)
{
	for (int i = 0; i < WEBAPI_URI_PARAM_REGIST_MAX; i++) {
		if (m_param[i].paramType == paramType) {
			return m_param[i].paramValue;
		}
	}
	return NULL;
}

// Extend
bool CWebApiUriParser::hasContentId()
{
	if (getParamOfContentId() != NULL) {
		return true;
	} else {
		return false;
	}
}

int CWebApiUriParser::getParamOfContentIdInt()
{
	if (hasContentId()) {
		return atoi(getParamOfContentId());
	}
	return 0;
}

bool CWebApiUriParser::hasTitleNo()
{
	if (getParamOfTitleNo() != NULL) {
		return true;
	} else {
		return false;
	}
}

int CWebApiUriParser::getParamOfTitleNoInt()
{
	if (hasTitleNo()) {
		return atoi(getParamOfTitleNo());
	}
	return 0;
}

bool CWebApiUriParser::hasIndex()
{
	if (getParamOfIndex() != NULL) {
		return true;
	} else {
		return false;
	}
}

int CWebApiUriParser::getParamOfIndexInt()
{
	if (hasIndex()) {
		return atoi(getParamOfIndex());
	}
	return 0;
}

bool CWebApiUriParser::isStorageType(WEBAPI_URI_STORAGE_TYPE storageType)
{
	const char* storageTypeStr = getParamOfStorageType();
	if (storageTypeStr == NULL) {
		return false;
	}

	if (isEqual(storageTypeStr, s_storageTypeTable[storageType].str)) {
		return true;
	}
	else {
		return false;
	}
}

bool CWebApiUriParser::isTitleType(WEBAPI_URI_TITLE_TYPE titleType)
{
	const char* titleTypeStr = getParamOfTitleType();
	if (titleTypeStr == NULL) {
		return false;
	}

	if (isEqual(titleTypeStr, s_titleTypeTable[titleType].str)) {
		return true;
	}
	else {
		return false;
	}
}

bool CWebApiUriParser::isStreamType(WEBAPI_URI_STREAM_TYPE streamType)
{
	const char* streamTypeStr = getParamOfStreamType();
	if (streamTypeStr == NULL) {
		return false;
	}

	if (isEqual(streamTypeStr, s_streamTypeTable[streamType].str)) {
		return true;
	}
	else {
		return false;
	}
}

bool CWebApiUriParser::isFolderType(WEBAPI_URI_FOLDER_TYPE folderType)
{
	const char* folderTypeStr = getParamOfFolderType();
	if (folderTypeStr == NULL) {
		return false;
	}

	if (isEqual(folderTypeStr, s_folderTypeTable[folderType].str)) {
		return true;
	}
	else {
		return false;
	}
}

bool CWebApiUriParser::isInvalidTriplet()
{
	if (getParamOfTriplet() == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool CWebApiUriParser::isChannel()
{
	if (getSchemeKey() == SCHEME_KEY_TV || getSchemeKey() == SCHEME_KEY_EXT) {
		return true;
	} else {
		return false;
	}
}
bool CWebApiUriParser::isChannelWithTriplet()
{
	if (isChannel() && !isInvalidTriplet()) {
		return true;
	} else {
		return false;
	}
}
bool CWebApiUriParser::isChannelWithoutTriplet()
{
	if (isChannel() && isInvalidTriplet()) {
		return true;
	} else {
		return false;
	}
}

ST_FD_INPUT_SOURCE_INFO CWebApiUriParser::getTriplet()
{
	ST_FD_INPUT_SOURCE_INFO triplet = {};
	triplet.m_eType = getInputType();

	if (isInvalidTriplet()) {
		return triplet;
	}

	char *tripletPos = NULL;
	char tempValue[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	strncpy(tempValue, getParamOfTriplet(), WEBAPI_URI_PARAM_VALUE_MAX);

	tripletPos = strtok(tempValue, ".");
	if (tripletPos == NULL) return triplet;
	triplet.m_stTriplet.m_network_id = atoi(tripletPos);

	tripletPos = strtok(NULL, ".");
	if (tripletPos == NULL) return triplet;
	triplet.m_stTriplet.m_ts_id = atoi(tripletPos);

	tripletPos = strtok(NULL, ".");
	if (tripletPos == NULL) return triplet;
	triplet.m_stTriplet.m_service_id = atoi(tripletPos);

	return triplet;
}

EN_FD_INPUT_TYPE CWebApiUriParser::getInputType()
{
	if (getSchemeValue() == SCHEME_VAL_ISDBT) {
		return FD_INPUT_TYPE_TRD;
	}
	else if (getSchemeValue() == SCHEME_VAL_ISDBBS) {
		return FD_INPUT_TYPE_BSD;
	}
	else if (getSchemeValue() == SCHEME_VAL_ISDBCS) {
		return FD_INPUT_TYPE_CSD;
	}
	else if (getSchemeValue() == SCHEME_VAL_VIDEO) {
		return FD_INPUT_TYPE_LINE;
	}
	else {
		return FD_INPUT_TYPE_INVALID;
	}
}

EN_CMH_DRIVE CWebApiUriParser::getDriveType()
{
	if (isStorageType(STORAGE_TYPE_INTERNAL_HDD)) {
		return CMH_DRIVE_HDD;
	}
	else if (isStorageType(STORAGE_TYPE_BD)) {
		return CMH_DRIVE_OPTDRV;
	}
	else if (isStorageType(STORAGE_TYPE_DVD)) {
		return CMH_DRIVE_OPTDRV;
	}
	else if (isStorageType(STORAGE_TYPE_CD)) {
		return CMH_DRIVE_OPTDRV;
	}
	else if (isStorageType(STORAGE_TYPE_USB1)) {
		return CMH_DRIVE_USB;
	}
	else if (isStorageType(STORAGE_TYPE_USB2)) {
		return CMH_DRIVE_USB2;
	}
	else {
		return CMH_DRIVE_DONT_CARE;
	}
}

EN_CMH_MEDIA_TYPE CWebApiUriParser::getMediaType()
{
	if (isStorageType(STORAGE_TYPE_INTERNAL_HDD)) {
		return CMH_MEDIA_TYPE_HDD;
	}
	else if (isStorageType(STORAGE_TYPE_BD)) {
		return CMH_MEDIA_TYPE_BD;
	}
	else if (isStorageType(STORAGE_TYPE_DVD)) {
		return CMH_MEDIA_TYPE_DVD;
	}
	else if (isStorageType(STORAGE_TYPE_CD)) {
		return CMH_MEDIA_TYPE_CD;
	}
	else if (isStorageType(STORAGE_TYPE_USB1)) {
		return CMH_MEDIA_TYPE_USB;
	}
	else if (isStorageType(STORAGE_TYPE_USB2)) {
		return CMH_MEDIA_TYPE_USB;
	}
	else {
		return CMH_MEDIA_TYPE_UNKNOWN;
	}
}

TTL_TYPE CWebApiUriParser::getTitleType()
{
	for (int i = 0; i < s_titleTypeNum; i++) {
		if (isTitleType(s_titleTypeTable[i].webapi_type)) {
			return s_titleTypeTable[i].ttl_type;
		}
	}
	return TTL_TYPE_ORIGINAL;
}

TTL_STRM CWebApiUriParser::getStreamType()
{
#if 0
	if (isStorageType(STORAGE_TYPE_DVD)) {
		return TTL_PS_STRM;
	}
	else {
		return TTL_TS_STRM;
	}
#else
	for (int i = 0; i < s_streamTypeNum; i++) {
		if (isStreamType(s_streamTypeTable[i].webapi_type)) {
			return s_streamTypeTable[i].stream_type;
		}
	}
	return TTL_UNKNOWN_STRM;
#endif
}

Ushort CWebApiUriParser::getFolderType()
{
	for (int i = 0; i < s_folderTypeNum; i++) {
		if (isFolderType(s_folderTypeTable[i].webapi_type)) {
			return s_folderTypeTable[i].folder_type;
		}
	}
	return TTL_UNKNOWN_FOLDER;
}

void CWebApiUriParser::createCTitleId(CTitleId* cTitleId)
{
	cTitleId->Clear();
	cTitleId->SetUniqueId(getParamOfContentIdInt());
	cTitleId->SetDrvId(getDriveType());
	cTitleId->SetTitleType(getTitleType());
	cTitleId->SetStrmType(getStreamType());
	cTitleId->SetFolderType(getFolderType());
}

void CWebApiUriParser::createUuid(char *buf, size_t bufSize)
{
	if (buf == NULL) return;
	static const char* UUID_PREFIX = "uuid:";
	size_t writable_size = bufSize;

	if (writable_size <= 0) return;
	memset(buf, 0, writable_size);
	strncpy(buf, UUID_PREFIX, writable_size);
	writable_size -= strlen(UUID_PREFIX);
	if (writable_size <= 0) return;
	if (!hasUuid()) return;
	strncat(buf, getParamOfUuid(), writable_size);
}

bool CWebApiUriParser::hasUuid()
{
	if (getParamOfUuid() != NULL) {
		return true;
	} else {
		return false;
	}
}

WEBAPI_URI_SOURCE_TYPE CWebApiUriParser::getSourceType()
{
	// TRD
	if (getSchemeValue() == SCHEME_VAL_ISDBT) {
		return SOURCE_TYPE_TRD;
	}
	// BS
	else if (getSchemeValue() == SCHEME_VAL_ISDBBS) {
		return SOURCE_TYPE_BSD;
	}
	// CS
	else if (getSchemeValue() == SCHEME_VAL_ISDBCS) {
		return SOURCE_TYPE_CSD;
	}
	// extInput:video
	else if (getSchemeValue() == SCHEME_VAL_VIDEO) {
		return SOURCE_TYPE_EXT_INPUT;
	}
	// HDD
	else if (getSchemeKey() == SCHEME_KEY_VIDEO && isStorageType(STORAGE_TYPE_INTERNAL_HDD)) {	// new
		return SOURCE_TYPE_INTERNAL_HDD;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_INTERNAL_HDD && m_type != URI_TYPE_MUSIC) {	// old
		return SOURCE_TYPE_INTERNAL_HDD;
	}
	// BD
	else if (isStorageType(STORAGE_TYPE_BD)) {	// new
		return SOURCE_TYPE_BD;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_BD) {	// old
		return SOURCE_TYPE_BD;
	}
	// DVD
	else if (isStorageType(STORAGE_TYPE_DVD)) {	// new
		return SOURCE_TYPE_DVD;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_DVD) {	// old
		return SOURCE_TYPE_DVD;
	}
	// CD
	else if (isStorageType(STORAGE_TYPE_CD)) {	// new
		return SOURCE_TYPE_CD;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_CD) {	// old
		return SOURCE_TYPE_CD;
	}
	// MUSIC
	else if (getSchemeKey() == SCHEME_KEY_AUDIO && isStorageType(STORAGE_TYPE_INTERNAL_HDD)) {	// new
		return SOURCE_TYPE_MUSIC;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_INTERNAL_HDD && m_type == URI_TYPE_MUSIC) {	// old
		return SOURCE_TYPE_MUSIC;
	}
	// USB1
	else if (isStorageType(STORAGE_TYPE_USB1)) {	// new
		return SOURCE_TYPE_USB1;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_USB1) {	// old
		return SOURCE_TYPE_USB1;
	}
	// USB2
	else if (isStorageType(STORAGE_TYPE_USB2)) {	// new
		return SOURCE_TYPE_USB2;
	}
	else if (getSchemeKey() == SCHEME_KEY_STORAGE && getSchemeValue() == SCHEME_VAL_USB2) {	// old
		return SOURCE_TYPE_USB2;
	}
	// HDD + USB2
	else if (isStorageType(STORAGE_TYPE_ALL)) {	// new
		return SOURCE_TYPE_ALL;
	}
	else if (getSchemeValue() == SCHEME_VAL_ALL) {	// old
		return SOURCE_TYPE_ALL;
	}
	// storage:*?path=TITLE
	else if (getSchemeValue() == SCHEME_VAL_ASTERISK) {
		return SOURCE_TYPE_PATH;
	}
	// Housemoving HDD
	else if (getSchemeKey() == SCHEME_KEY_HOUSEMOVING && isStorageType(STORAGE_TYPE_INTERNAL_HDD)) {
		return SOURCE_TYPE_HOUSEMOVING_HDD;
	}
	// Housemoving USB
	else if (getSchemeKey() == SCHEME_KEY_HOUSEMOVING && isStorageType(STORAGE_TYPE_USB2)) {
		return SOURCE_TYPE_HOUSEMOVING_USB;
	}
	else {
		return SOURCE_TYPE_INVALID;
	}
}

bool CWebApiUriParser::hasPath()
{
	if (getParamOfPath() != NULL) {
		return true;
	} else {
		return false;
	}
}

bool CWebApiUriParser::hasTitlePath()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return false;
	}
	if (isMatch(path, URI_STR_PATH_TITLE)) {
		return true;
	}
	return false;
}

bool CWebApiUriParser::hasRecordingTypePath()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return false;
	}
	if (isMatch(path, URI_STR_PATH_RECORDINGTYPE)) {
		return true;
	}
	return false;
}

bool CWebApiUriParser::hasAlbumPath()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return false;
	}
	if (isMatch(path, URI_STR_PATH_ALBUM)) {
		return true;
	}
	return false;
}

bool CWebApiUriParser::hasArtistPath()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return false;
	}
	if (isMatch(path, URI_STR_PATH_ARTIST)) {
		return true;
	}
	return false;
}

const char* CWebApiUriParser::getTitlePathName()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return NULL;
	}
	if (isMatch(path, URI_STR_PATH_TITLE)) {
		path += strlen(URI_STR_PATH_TITLE);
		WA_DEBUG("Path Name[%s]\n",path);
		return path;
	}
	return NULL;
}

int CWebApiUriParser::getTitlePathId()
{
	if (hasPath()) {
		return atoi(getTitlePathName());
	}
	return 0;
}

const char* CWebApiUriParser::getRecordingTypePathName()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return NULL;
	}
	if (isMatch(path, URI_STR_PATH_RECORDINGTYPE)) {
		path += strlen(URI_STR_PATH_RECORDINGTYPE);
		WA_DEBUG("Path Name[%s]\n",path);
		return path;
	}
	return NULL;
}

int CWebApiUriParser::getRecordingTypePathId()
{
	if (hasPath()) {
		return atoi(getRecordingTypePathName());
	}
	return 0;
}

const char* CWebApiUriParser::getAlbumPathName()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return NULL;
	}
	if (isMatch(path, URI_STR_PATH_ALBUM)) {
		path += strlen(URI_STR_PATH_ALBUM);
		WA_DEBUG("Path Name[%s]\n",path);
		return path;
	}
	return NULL;
}

int CWebApiUriParser::getAlbumPathId()
{
	if (hasPath()) {
		return atoi(getAlbumPathName());
	}
	return 0;
}

const char* CWebApiUriParser::getArtistPathName()
{
	const char* path = getParamOfPath();
	if (path == NULL) {
		return NULL;
	}
	if (isMatch(path, URI_STR_PATH_ARTIST)) {
		path += strlen(URI_STR_PATH_ARTIST);
		WA_DEBUG("Path Name[%s]\n",path);
		return path;
	}
	return NULL;
}

int CWebApiUriParser::getArtistPathId()
{
	if (hasPath()) {
		return atoi(getArtistPathName());
	}
	return 0;
}

bool CWebApiUriParser::hasExternalDevice()
{
	const char* usbDeviceType = getParamOfUsbDeviceType();
	if (usbDeviceType == NULL) {
		return false;
	}
	if (isMatch(usbDeviceType, URI_STR_EXTERNAL_DEVICE)) {
		return true;
	}
	return false;
}

// Utile
void CWebApiUriParser::toLower()
{
	for (int i = 0; i < (int)m_len; i++) {
		m_uri[i] = tolower(m_uri[i]);
	}
}

bool CWebApiUriParser::isEqual(const char* str1, const char* str2)
{
	return _isEqual(str1, str2);
}

bool CWebApiUriParser::isMatch(const char* str1, const char* str2)
{
	return _isMatch(str1, str2);
}

/*-----------------------------------------------------------
 CWebApiUriCreator
-----------------------------------------------------------*/
CWebApiUriCreator::CWebApiUriCreator()
{
	WA_TRACE();
	init();
}

CWebApiUriCreator::CWebApiUriCreator(WEBAPI_URI_SCHEME_KEY schemeKey, WEBAPI_URI_SCHEME_VAL schemeValue)
{
	WA_TRACE();
	init();
	createScheme(schemeKey, schemeValue);
}

CWebApiUriCreator::CWebApiUriCreator(EN_FD_INPUT_TYPE inputType, ST_TRIPLET_INFO& triplet)
{
	WA_TRACE();
	init();
	createTriplet(inputType, triplet);
}

CWebApiUriCreator::CWebApiUriCreator(EN_FD_CAS_TYPE casType, ST_TRIPLET_INFO& triplet)
{
	WA_TRACE();
	init();
	createTriplet(casType, triplet);
}

CWebApiUriCreator::CWebApiUriCreator(WEBAPI_URI_STORAGE_TYPE storageType)
{
	WA_TRACE();
	init();
	createStorage(storageType);
}

CWebApiUriCreator::CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet)
{
	WA_TRACE();
	init();
	switch (sourceType) {
	case SOURCE_TYPE_TRD:
		createTriplet(FD_INPUT_TYPE_TRD, triplet);
		break;
	case SOURCE_TYPE_BSD:
		createTriplet(FD_INPUT_TYPE_BSD, triplet);
		break;
	case SOURCE_TYPE_CSD:
		createTriplet(FD_INPUT_TYPE_CSD, triplet);
		break;
	case SOURCE_TYPE_EXT_INPUT:
		createScheme(SCHEME_KEY_EXT, SCHEME_VAL_VIDEO);
		break;
	default:
		WA_ERROR("Invalid SourceType(%d)\n",sourceType);
		break;
	}
}

CWebApiUriCreator::CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, int contentId)
{
	WA_TRACE();
	init();
	switch (sourceType) {
	case SOURCE_TYPE_INTERNAL_HDD:
		createScheme(SCHEME_KEY_VIDEO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_INTERNAL_HDD);
		break;
	case SOURCE_TYPE_BD:
		createScheme(SCHEME_KEY_VIDEO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_BD);
		break;
	case SOURCE_TYPE_DVD:
		createScheme(SCHEME_KEY_VIDEO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_DVD);
		break;
	case SOURCE_TYPE_USB1:
		createScheme(SCHEME_KEY_VIDEO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_USB1);
		break;
	case SOURCE_TYPE_USB2:
		createScheme(SCHEME_KEY_VIDEO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_USB2);
		break;
	case SOURCE_TYPE_CD:
		createScheme(SCHEME_KEY_AUDIO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_CD);
		break;
	case SOURCE_TYPE_MUSIC:
		createScheme(SCHEME_KEY_AUDIO, SCHEME_VAL_CONTENT);
		addContentId(contentId);
		addStorageType(STORAGE_TYPE_INTERNAL_HDD);
		break;
	default:
		WA_ERROR("Invalid SourceType(%d)\n",sourceType);
		break;
	}
}

CWebApiUriCreator::CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, CTitleId& cTitleId)
{
	WA_TRACE();
	init();
	WEBAPI_URI_SCHEME_KEY schemeKey = SCHEME_KEY_INVALID;
	WEBAPI_URI_SCHEME_VAL schemeValue = SCHEME_VAL_INVALID;
	switch (sourceType) {
	case SOURCE_TYPE_HOUSEMOVING_HDD:
	case SOURCE_TYPE_HOUSEMOVING_USB:
		schemeKey = SCHEME_KEY_HOUSEMOVING;
		schemeValue = SCHEME_VAL_MOVIE;
		break;
	case SOURCE_TYPE_MUSIC:
	case SOURCE_TYPE_CD:
		schemeKey = SCHEME_KEY_AUDIO;
		schemeValue = SCHEME_VAL_CONTENT;
		break;
	default:
		schemeKey = SCHEME_KEY_VIDEO;
		schemeValue = SCHEME_VAL_CONTENT;
		break;
	}
	createScheme(schemeKey, schemeValue);
	addStorageType(getStorageType(sourceType));
	addTitleId(cTitleId);
}

CWebApiUriCreator::~CWebApiUriCreator()
{
}

// Base
void CWebApiUriCreator::createScheme(WEBAPI_URI_SCHEME_KEY schemeKey, WEBAPI_URI_SCHEME_VAL schemeValue)
{
	init();
	appendUri(s_schemeKeyTable[schemeKey].str);
	appendUri(":");
	if (schemeValue != SCHEME_VAL_INVALID) {
		appendUri(s_schemeValueTable[schemeValue].str);
	}
}

void CWebApiUriCreator::createTriplet(EN_FD_INPUT_TYPE inputType, ST_TRIPLET_INFO& triplet)
{
	init();
	if (inputType == FD_INPUT_TYPE_LINE) {
		createScheme(SCHEME_KEY_EXT, SCHEME_VAL_VIDEO);
	} else {
		appendUri(URI_STR_TV);
		appendUri(":");
		appendUri(s_inputTypeTable[inputType].str);
		addTriplet(triplet);
	}
}

void CWebApiUriCreator::createTriplet(EN_FD_CAS_TYPE casType, ST_TRIPLET_INFO& triplet)
{
	init();
	if(FD_CAS_HDD == casType){
		appendUri(URI_STR_STORAGE);
		appendUri(":");
	}else{
		appendUri(URI_STR_TV);
		appendUri(":");
		appendUri(s_casTypeTable[casType].str);
		
		if((FD_CAS_TRD == casType) ||(FD_CAS_BSD == casType)||(FD_CAS_CSD == casType) ){
		    addTriplet(triplet);
		}
	}
}

void CWebApiUriCreator::createStorage(WEBAPI_URI_STORAGE_TYPE storageType)
{
	init();
	appendUri(URI_STR_STORAGE);
	appendUri(":");
	appendUri(s_storageTypeTable[storageType].str);
}

void CWebApiUriCreator::addParam(WEBAPI_URI_PARAM_TYPE paramType, const char* paramValue)
{
	if (m_isFirstParam) {
		appendUri("?");
		m_isFirstParam = false;
	}
	else {
		appendUri("&");
	}

	appendUri(s_paramTypeTable[paramType].str);
	appendUri("=");
	if (paramValue == NULL) {
		WA_ERROR("Invalid Param value\n");
		paramValue = URI_STR_INVALID;
	}
	appendUri(paramValue);
}

void CWebApiUriCreator::addParam(WEBAPI_URI_PARAM_TYPE paramType, int paramValueInt)
{
	char valueStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(valueStr, WEBAPI_URI_PARAM_VALUE_MAX, "%d", paramValueInt);
	addParam(paramType, valueStr);
}

// Extend
void CWebApiUriCreator::addContentId(const char* contentId)
{
	addParam(PARAM_TYPE_CONTENT_ID, contentId);
}

void CWebApiUriCreator::addContentId(int contentId)
{
	if (contentId >= 0) {
		addParam(PARAM_TYPE_CONTENT_ID, contentId);
	}
}

void CWebApiUriCreator::addStorageType(WEBAPI_URI_STORAGE_TYPE storageType)
{
	addParam(PARAM_TYPE_STORAGE_TYPE, s_storageTypeTable[storageType].str);
}

void CWebApiUriCreator::addTitleType(TTL_TYPE titleType)
{
	WA_DEBUG("TitleType[0x%08x]\n",titleType);
	for (int i = 0; i < s_titleTypeNum; i++) {
		if (s_titleTypeTable[i].ttl_type == titleType) {
			addParam(PARAM_TYPE_TITLE_TYPE, s_titleTypeTable[i].str);
			return;
		}
	}
	addParam(PARAM_TYPE_TITLE_TYPE, URI_STR_INVALID);
}

void CWebApiUriCreator::addStreamType(TTL_STRM streamType)
{
	for (int i = 0; i < s_streamTypeNum; i++) {
		if (s_streamTypeTable[i].stream_type == streamType) {
			addParam(PARAM_TYPE_STREAM_TYPE, s_streamTypeTable[i].str);
			return;
		}
	}
	addParam(PARAM_TYPE_STREAM_TYPE, URI_STR_INVALID);
}

void CWebApiUriCreator::addFolderType(Ushort folderType)
{
	for (int i = 0; i < s_folderTypeNum; i++) {
		if (s_folderTypeTable[i].folder_type == folderType) {
			addParam(PARAM_TYPE_FOLDER_TYPE, s_folderTypeTable[i].str);
			return;
		}
	}
	addParam(PARAM_TYPE_FOLDER_TYPE, URI_STR_INVALID);
}

void CWebApiUriCreator::addTitleNo(int titleNo)
{
	addParam(PARAM_TYPE_TITLE_NO, titleNo);
}

void CWebApiUriCreator::addIndex(int index)
{
	addParam(PARAM_TYPE_INDEX, index);
}

void CWebApiUriCreator::addTriplet(ST_TRIPLET_INFO& triplet)
{
	char tripStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(tripStr, WEBAPI_URI_PARAM_VALUE_MAX, "%d.%d.%d"
									, triplet.m_network_id
									, triplet.m_ts_id
									, triplet.m_service_id);
	addParam(PARAM_TYPE_TRIPLET, tripStr);
}

void CWebApiUriCreator::addTitlePathName(const char* titleName)
{
	char pathStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(pathStr, WEBAPI_URI_PARAM_VALUE_MAX
		, "%s%s"
		, URI_STR_PATH_TITLE
		, titleName);
	addParam(PARAM_TYPE_PATH, pathStr);
}

void CWebApiUriCreator::addTitlePathId(int titleId)
{
	char pathStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(pathStr, WEBAPI_URI_PARAM_VALUE_MAX
		, "%s%d"
		, URI_STR_PATH_TITLE
		, titleId);
	addParam(PARAM_TYPE_PATH, pathStr);
}

void CWebApiUriCreator::addRecordingTypePathId(int titleId)
{
	char pathStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(pathStr, WEBAPI_URI_PARAM_VALUE_MAX
		, "%s%d"
		, URI_STR_PATH_RECORDINGTYPE
		, titleId);
	addParam(PARAM_TYPE_PATH, pathStr);
}

void CWebApiUriCreator::addAlbumPathId(int albumId)
{
	char pathStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(pathStr, WEBAPI_URI_PARAM_VALUE_MAX
		, "%s%d"
		, URI_STR_PATH_ALBUM
		, albumId);
	addParam(PARAM_TYPE_PATH, pathStr);
}

void CWebApiUriCreator::addArtistPathId(int artistId)
{
	char pathStr[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(pathStr, WEBAPI_URI_PARAM_VALUE_MAX
		, "%s%d"
		, URI_STR_PATH_ARTIST
		, artistId);
	addParam(PARAM_TYPE_PATH, pathStr);
}

void CWebApiUriCreator::addTitleId(CTitleId& cTitleId)
{
	addContentId(cTitleId.GetUniqueId());
	addTitleType(cTitleId.GetTitleType());
	addStreamType(cTitleId.GetStrmType());
	addFolderType(cTitleId.GetFolderType());
}

void CWebApiUriCreator::addUuid(const char* uuid)
{
	static const char* UUID_FORMAT = "uuid:";
	if (uuid && isMatch(uuid, UUID_FORMAT)) {
		addParam(PARAM_TYPE_UUID, uuid + strlen(UUID_FORMAT));
	}
}

// Util
void CWebApiUriCreator::appendUri(const char* str)
{
	size_t uri_len = strlen(m_uri);
	size_t writable_size = WEBAPI_URI_STRING_MAX - uri_len;
	if (writable_size > 0) {
		strncat(m_uri + uri_len, str, writable_size);
	}
}

bool CWebApiUriCreator::isEqual(const char* str1, const char* str2)
{
	return _isEqual(str1, str2);
}

bool CWebApiUriCreator::isMatch(const char* str1, const char* str2)
{
	return _isMatch(str1, str2);
}

WEBAPI_URI_STORAGE_TYPE CWebApiUriCreator::getStorageType(WEBAPI_URI_SOURCE_TYPE sourceType)
{
	WA_TRACE();
	switch (sourceType) {
	case SOURCE_TYPE_INTERNAL_HDD:			return STORAGE_TYPE_INTERNAL_HDD;
	case SOURCE_TYPE_BD:					return STORAGE_TYPE_BD;
	case SOURCE_TYPE_DVD:					return STORAGE_TYPE_DVD;
	case SOURCE_TYPE_USB1:					return STORAGE_TYPE_USB1;
	case SOURCE_TYPE_USB2:					return STORAGE_TYPE_USB2;
	case SOURCE_TYPE_CD:					return STORAGE_TYPE_CD;
	case SOURCE_TYPE_MUSIC:					return STORAGE_TYPE_INTERNAL_HDD;
	case SOURCE_TYPE_ALL:					return STORAGE_TYPE_ALL;
	case SOURCE_TYPE_HOUSEMOVING_HDD:		return STORAGE_TYPE_INTERNAL_HDD;
	case SOURCE_TYPE_HOUSEMOVING_USB:		return STORAGE_TYPE_USB2;
	default:
		WA_ERROR("Invalid SourceType(%d)\n",sourceType);
		return STORAGE_TYPE_INVALID;
	}
}

WEBAPI_URI_STORAGE_TYPE CWebApiUriCreator::getStorageType(EN_CMH_DRIVE driveType)
{
	switch (driveType) {
	case CMH_DRIVE_HDD:			return STORAGE_TYPE_INTERNAL_HDD;
	case CMH_DRIVE_USB:			return STORAGE_TYPE_USB1;
	case CMH_DRIVE_USB2:		return STORAGE_TYPE_USB2;
	// case CMH_DRIVE_OPTDRV:		return STORAGE_TYPE_BD;
	default:
		WA_ERROR("Invalid DriveType(%d)\n",driveType);
		return STORAGE_TYPE_INVALID;
	}
}

WEBAPI_URI_STORAGE_TYPE CWebApiUriCreator::getStorageType(EN_CMH_MEDIA_TYPE mediaType)
{
	switch (mediaType) {
	case CMH_MEDIA_TYPE_HDD:	return STORAGE_TYPE_INTERNAL_HDD;
	case CMH_MEDIA_TYPE_BD:		return STORAGE_TYPE_BD;
	case CMH_MEDIA_TYPE_DVD:	return STORAGE_TYPE_DVD;
	case CMH_MEDIA_TYPE_USB:	return STORAGE_TYPE_USB2;
	case CMH_MEDIA_TYPE_CD:		return STORAGE_TYPE_CD;
	default:
		WA_ERROR("Invalid MediaType(%d)\n",mediaType);
		return STORAGE_TYPE_INVALID;
	}
}

/*-----------------------------------------------------------
 CWebApiThumbnailUrlCreator
-----------------------------------------------------------*/
CWebApiThumbnailUrlCreator::CWebApiThumbnailUrlCreator(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId)
{
	WA_TRACE();
	init();
	createThumbnail(sourceType, uniqueId);
}

CWebApiThumbnailUrlCreator::CWebApiThumbnailUrlCreator(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet, THUMBNAIL_ICON_TYPE type)
{
	WA_TRACE();
	init();
	createIcon(sourceType, triplet, type);
}

CWebApiThumbnailUrlCreator::CWebApiThumbnailUrlCreator(const char* uuid, WEBAPI_URI_STORAGE_TYPE storageType, Uint32 uniqueId)
{
	WA_TRACE();
	init();
	createHousemoving(uuid, storageType, uniqueId);
}

CWebApiThumbnailUrlCreator::~CWebApiThumbnailUrlCreator()
{
}

void CWebApiThumbnailUrlCreator::createThumbnail(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId)
{
	WA_TRACE();

	const char* storageType = NULL;
	switch (sourceType) {
	case SOURCE_TYPE_INTERNAL_HDD:
		storageType = URI_STR_INTERNAL_HDD;
		break;
	case SOURCE_TYPE_USB1:
		storageType = URI_STR_USB1;
		break;
	case SOURCE_TYPE_USB2:
		storageType = URI_STR_USB2;
		break;
	case SOURCE_TYPE_BD:
		storageType = URI_STR_BD;
		break;
	case SOURCE_TYPE_DVD:
		storageType = URI_STR_DVD;
		break;
	default:
		WA_ERROR("SourceType Error(%d)\n",sourceType);
		return;
	}

	/* http://localhost:50100/thumbnail/{storageType}/{uniqueId}.jpg  */
	snprintf(m_thumbnailUrl, WEBAPI_URI_STRING_MAX,
             "http://localhost:50100/thumbnail/%s/%d.jpg",
             storageType,
             uniqueId);
	WA_DEBUG("thumbnailUrl[%s]\n",m_thumbnailUrl);
}

void CWebApiThumbnailUrlCreator::createIcon(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet, THUMBNAIL_ICON_TYPE type)
{
	WA_TRACE();

	const char* serviceType = NULL;
	switch (sourceType) {
	case SOURCE_TYPE_TRD:
		serviceType = "TRD";
		break;
	case SOURCE_TYPE_BSD:
		serviceType = "BSD";
		break;
	case SOURCE_TYPE_CSD:
		serviceType = "CSD";
		break;
	default:
		WA_ERROR("SourceType Error(%d)\n",sourceType);
		return;
	}
	const char* thumbnaiType = (type == THUMBNAIL_ICON_TYPE_HD) ? "HD" : "SD";

	/* http://localhost:50100/icon/{TRD/BSD/CSD}/{TRD/BSD/CSD}-{serviceID}-{HD/SD}.png */
	snprintf(m_thumbnailUrl, WEBAPI_URI_STRING_MAX,
		"http://localhost:50100/icon/%s/%s-%d-%s.png"
									, serviceType
									, serviceType
									, triplet.m_service_id
									, thumbnaiType);
	WA_DEBUG("thumbnailUrl[%s]\n",m_thumbnailUrl);
}

void CWebApiThumbnailUrlCreator::createHousemoving(const char* uuid, WEBAPI_URI_STORAGE_TYPE storageType, Uint32 uniqueId)
{
	WA_TRACE();
	const char* uuidStr = NULL;
	const char* storageTypeStr = NULL;
	const char* uniqueIdStr = NULL;
	static const char* UUID_FORMAT = "uuid:";

	// uuid
	if (uuid && isMatch(uuid, UUID_FORMAT)) {
		uuidStr = uuid + strlen(UUID_FORMAT);
	} else {
		return;
	}
	// storage type
	storageTypeStr = s_storageTypeTable[storageType].str;
	// unique id
	char uniqueIdValue[WEBAPI_URI_PARAM_VALUE_MAX + 1] = {};
	snprintf(uniqueIdValue, WEBAPI_URI_PARAM_VALUE_MAX, "%ld", uniqueId);
	uniqueIdStr = uniqueIdValue;

	/* http://localhost:50100/housemoving/{uuid}/{storageType}/{uniqueId}.jpg  */
	snprintf(m_thumbnailUrl, WEBAPI_URI_STRING_MAX,
		"http://localhost:50100/housemoving/%s/%s/%s.png"
									, uuidStr
									, storageTypeStr
									, uniqueIdStr);
	WA_DEBUG("HousemovingThumbnail[%s]\n",m_thumbnailUrl);
}

bool CWebApiThumbnailUrlCreator::isEqual(const char* str1, const char* str2)
{
	return _isEqual(str1, str2);
}

bool CWebApiThumbnailUrlCreator::isMatch(const char* str1, const char* str2)
{
	CWebApiPathCreator path = CWebApiPathCreator::CreateThumbnailPath(SOURCE_TYPE_TRD, 0);
	printf("path=%s\n",path.getPath());
	const char* test = CWebApiPathCreator::CreateThumbnailPath(SOURCE_TYPE_TRD, 0).getPath();
	printf("path=%s\n",test);
	return _isMatch(str1, str2);
}

/*-----------------------------------------------------------
 CWebApiPathCreator
-----------------------------------------------------------*/
CWebApiPathCreator CWebApiPathCreator::CreateThumbnailPath(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId)
{
	WA_TRACE()
	CWebApiPathCreator pathCreator;
	pathCreator.createThumbnail(sourceType, uniqueId);
	return pathCreator;
}

void CWebApiPathCreator::createThumbnail(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId)
{

}

