/**
 * Sony CONFIDENTIAL
 * Copyright (C) 2015 Sony Corporation, All Rights Reserved.
 * @file   $File: //depot/UNI-SYSTEM-RE/BASELINE/NetService/Common/WebApiUri.h $
 * @brief  
 * @author 
 */

#ifndef __WEBAPI_URI_H__
#define __WEBAPI_URI_H__

// Facade
#include "IF/Util/FacadeDefs.h"
#include "Media_Id.h"
#include "TitleId.h"

/*-----------------------------------------------------------
  Define
 -----------------------------------------------------------*/
#define WEBAPI_URI_STRING_MAX							(512)
#define WEBAPI_URI_PARAM_VALUE_MAX						(256 + 10)
#define WEBAPI_URI_PARAM_REGIST_MAX						(6)

/*-----------------------------------------------------------
  Enum
 -----------------------------------------------------------*/
enum WEBAPI_URI_SCHEME_KEY {
	SCHEME_KEY_INVALID,
	SCHEME_KEY_TV,
	SCHEME_KEY_EXT,
	SCHEME_KEY_VIDEO,
	SCHEME_KEY_AUDIO,
	SCHEME_KEY_STORAGE,
	SCHEME_KEY_HOUSEMOVING,
};

enum WEBAPI_URI_SCHEME_VAL {
	SCHEME_VAL_INVALID,
	SCHEME_VAL_ISDBT,
	SCHEME_VAL_ISDBBS,
	SCHEME_VAL_ISDBCS,
	SCHEME_VAL_VIDEO,
	SCHEME_VAL_CONTENT,
	SCHEME_VAL_INTERNAL_HDD,
	SCHEME_VAL_BD,
	SCHEME_VAL_DVD,
	SCHEME_VAL_CD,
	SCHEME_VAL_USB1,
	SCHEME_VAL_USB2,
	SCHEME_VAL_ALL,
	SCHEME_VAL_ASTERISK,
	SCHEME_VAL_STORAGE,
	SCHEME_VAL_MOVIE,
};

enum WEBAPI_URI_PARAM_TYPE {
	PARAM_TYPE_INVALID,
	PARAM_TYPE_TRIPLET,
	PARAM_TYPE_CONTENT_ID,
	PARAM_TYPE_STORAGE_TYPE,
	PARAM_TYPE_TITLE_TYPE,
	PARAM_TYPE_STREAM_TYPE,
	PARAM_TYPE_FOLDER_TYPE,
	PARAM_TYPE_TITLE_NO,
	PARAM_TYPE_INDEX,
	PARAM_TYPE_PATH,
	PARAM_TYPE_USB_DEVICE_TYPE,
	PARAM_TYPE_UUID,
};

enum WEBAPI_URI_STORAGE_TYPE {
	STORAGE_TYPE_INVALID,
	STORAGE_TYPE_INTERNAL_HDD,
	STORAGE_TYPE_BD,
	STORAGE_TYPE_DVD,
	STORAGE_TYPE_CD,
	STORAGE_TYPE_USB1,
	STORAGE_TYPE_USB2,
	STORAGE_TYPE_ALL,
};

enum WEBAPI_URI_TITLE_TYPE {
	TITLE_TYPE_NONE,
	TITLE_TYPE_UNKNOWN,
	TITLE_TYPE_ORIGINAL,
	TITLE_TYPE_PLAYLIST,
	TITLE_TYPE_TOPMENU,
	TITLE_TYPE_MENU,
	TITLE_TYPE_AUTOPLAY,
	TITLE_TYPE_FREEORG,
	TITLE_TYPE_FREEPL,
	TITLE_TYPE_FREE,
	TITLE_TYPE_BDREAL,
	TITLE_TYPE_BDVIRTUAL,
	TITLE_TYPE_ACTV,
	TITLE_TYPE_PICORIGINAL,
	TITLE_TYPE_PICLARGE,
	TITLE_TYPE_PICMIDDLE,
	TITLE_TYPE_PICSMALL,
	TITLE_TYPE_PICTHUMB,
	TITLE_TYPE_FOLDER,
	TITLE_TYPE_XPICSTORY,
	TITLE_TYPE_XSCRAPBOOK,
	TITLE_TYPE_STILLALL,
	TITLE_TYPE_BGM,
	TITLE_TYPE_MUSIC,
	TITLE_TYPE_AVCHD,
	TITLE_TYPE_ONETOUCHDISC,
	TITLE_TYPE_AVCHDALL,
	TITLE_TYPE_AVCHDDIFF,
	TITLE_TYPE_AVCHDALLDISC,
	TITLE_TYPE_AVCHDDIFFDISC,
	TITLE_TYPE_INVALID,
	TITLE_TYPE_NOTVISIBLE,
	TITLE_TYPE_SAMPLE,
	TITLE_TYPE_KLEIOODEKAKE,
	TITLE_TYPE_MP4,
	TITLE_TYPE_MP4_4K,
};

enum WEBAPI_URI_STREAM_TYPE {
	STREAM_TYPE_UNKNOWN,
	STREAM_TYPE_PS,
	STREAM_TYPE_TS,
	STREAM_TYPE_SOUND,
	STREAM_TYPE_PICTURE,
	STREAM_TYPE_FOLDER,
	STREAM_TYPE_IMAGE,
	STREAM_TYPE_BGM,
	STREAM_TYPE_AVC,
	STREAM_TYPE_SCRAP,
	STREAM_TYPE_AVCHD,
};

enum WEBAPI_URI_FOLDER_TYPE {
	FOLDER_TYPE_UNKNOWN,
	FOLDER_TYPE_ROOT,
	FOLDER_TYPE_VIDEO_ROOT,
	FOLDER_TYPE_ALBUM,
	FOLDER_TYPE_ROOT_XPIC,
	FOLDER_TYPE_ROOT_SAMPLE,
	FOLDER_TYPE_DVDMENU,
	FOLDER_TYPE_SAMPLE_ALBUM,
	FOLDER_TYPE_ROOT_XSCRAP,
	FOLDER_TYPE_XPIC_THUM,
	FOLDER_TYPE_XSCRAP_THUM,
	FOLDER_TYPE_XPIC_EFFECT,
	FOLDER_TYPE_XSCRAP_TEMP,
	FOLDER_TYPE_XSCRAP_THEME,
	FOLDER_TYPE_ROOT_FREE_AREA,
	FOLDER_TYPE_BDJMENU,
};

enum WEBAPI_URI_SOURCE_TYPE
{
	SOURCE_TYPE_INVALID = 0,
	SOURCE_TYPE_TRD,
	SOURCE_TYPE_BSD,
	SOURCE_TYPE_CSD,
	SOURCE_TYPE_EXT_INPUT,
	SOURCE_TYPE_BD,
	SOURCE_TYPE_DVD,
	SOURCE_TYPE_INTERNAL_HDD,
	SOURCE_TYPE_CD,
	SOURCE_TYPE_MUSIC,
	SOURCE_TYPE_USB1,
	SOURCE_TYPE_USB2,
	SOURCE_TYPE_ALL,
	SOURCE_TYPE_PATH,
	SOURCE_TYPE_HOUSEMOVING_HDD,
	SOURCE_TYPE_HOUSEMOVING_USB,
};

enum WEBAPI_URI_TYPE {
	URI_TYPE_NONE,
	URI_TYPE_MOVIE,
	URI_TYPE_MOVIE_AVCHD,
	URI_TYPE_MOVIE_MP4,
	URI_TYPE_MUSIC,
};

/*-----------------------------------------------------------
  CWebApiUriParser
 -----------------------------------------------------------*/
class CWebApiUriParser
{
private:
	struct ParamType {
		WEBAPI_URI_PARAM_TYPE paramType;
		char paramValue[WEBAPI_URI_PARAM_VALUE_MAX + 1];
	};

public:
	CWebApiUriParser(const char* uri);
	CWebApiUriParser(const char* uri, const char* type);
	virtual ~CWebApiUriParser();

public:
	bool isInvalid() { return m_isValid ? false : true; }
	bool isEmpty() { return m_len > 0 ? false : true; }
	WEBAPI_URI_SCHEME_KEY getSchemeKey() { return m_schemeKey; }
	WEBAPI_URI_SCHEME_VAL getSchemeValue() { return m_schemeVal; }
	const char* getParamValue(WEBAPI_URI_PARAM_TYPE paramType);
	const char* getParamOfTriplet() { return getParamValue(PARAM_TYPE_TRIPLET); }
	const char* getParamOfContentId() { return getParamValue(PARAM_TYPE_CONTENT_ID); }
	const char* getParamOfStorageType() { return getParamValue(PARAM_TYPE_STORAGE_TYPE); }
	const char* getParamOfTitleType() { return getParamValue(PARAM_TYPE_TITLE_TYPE); }
	const char* getParamOfStreamType() { return getParamValue(PARAM_TYPE_STREAM_TYPE); }
	const char* getParamOfFolderType() { return getParamValue(PARAM_TYPE_FOLDER_TYPE); }
	const char* getParamOfTitleNo() { return getParamValue(PARAM_TYPE_TITLE_NO); }
	const char* getParamOfIndex() { return getParamValue(PARAM_TYPE_INDEX); }
	const char* getParamOfPath() { return getParamValue(PARAM_TYPE_PATH); }
	const char* getParamOfUsbDeviceType() { return getParamValue(PARAM_TYPE_USB_DEVICE_TYPE); }
	const char* getParamOfUuid() { return getParamValue(PARAM_TYPE_UUID); }
	bool hasContentId();
	bool hasTitleNo();
	bool hasIndex();
	bool hasPath();
	bool hasExternalDevice();
	bool hasUuid();
	int getParamOfContentIdInt();
	int getParamOfTitleNoInt();
	int getParamOfIndexInt();
	bool isStorageType(WEBAPI_URI_STORAGE_TYPE storageType);
	bool isTitleType(WEBAPI_URI_TITLE_TYPE titleType);
	bool isStreamType(WEBAPI_URI_STREAM_TYPE streamType);
	bool isFolderType(WEBAPI_URI_FOLDER_TYPE folderType);
	bool isInvalidTriplet();
	bool isChannel();
	bool isChannelWithTriplet();
	bool isChannelWithoutTriplet();
	ST_FD_INPUT_SOURCE_INFO getTriplet();
	EN_FD_INPUT_TYPE getInputType();
	EN_CMH_DRIVE getDriveType();
	EN_CMH_MEDIA_TYPE getMediaType();
	TTL_TYPE getTitleType();
	TTL_STRM getStreamType();
	Ushort getFolderType();
	WEBAPI_URI_SOURCE_TYPE getSourceType();
	bool hasTitlePath();
	const char* getTitlePathName();
	int getTitlePathId();
	bool hasRecordingTypePath();
	const char* getRecordingTypePathName();
	int getRecordingTypePathId();
	bool hasAlbumPath();
	const char* getAlbumPathName();
	int getAlbumPathId();
	bool hasArtistPath();
	const char* getArtistPathName();
	int getArtistPathId();

	void createCTitleId(CTitleId* cTitleId);
	void createUuid(char *buf, size_t bufSize);
	bool isTypeOf(WEBAPI_URI_TYPE type);


private:
	int parse();
	int parseSchemeKey(const char* str);
	int parseSchemeValue(const char* str);
	int parseParam(const char* str, int paramIndex);
	void setParam(WEBAPI_URI_PARAM_TYPE type, char* str, ParamType& param);

	void toLower();
	bool isEqual(const char* str1, const char* str2);
	bool isMatch(const char* str1, const char* str2);

	void setType(const char* type);

private:
	CWebApiUriParser()
		: m_isValid(false)
		, m_len()
		, m_schemeKey()
		, m_schemeVal()
		, m_uri()
		, m_param()
		, m_type(URI_TYPE_NONE)
	{}
	void init()
	{
		m_isValid = false;
		m_len = 0;
		m_schemeKey = SCHEME_KEY_INVALID;
		m_schemeVal = SCHEME_VAL_INVALID;
		memset(m_uri, 0, sizeof(m_uri));
		memset(m_param, 0, sizeof(m_param));
		m_type = URI_TYPE_NONE;
	}

private:
	bool					m_isValid;
	size_t					m_len;
	WEBAPI_URI_SCHEME_KEY	m_schemeKey;
	WEBAPI_URI_SCHEME_VAL	m_schemeVal;
	char					m_uri[WEBAPI_URI_STRING_MAX+1];
	ParamType				m_param[WEBAPI_URI_PARAM_REGIST_MAX];
	WEBAPI_URI_TYPE 		m_type;
};

/*-----------------------------------------------------------
 CWebApiUriCreator
-----------------------------------------------------------*/
class CWebApiUriCreator
{
public:
	CWebApiUriCreator();
	CWebApiUriCreator(WEBAPI_URI_SCHEME_KEY schemeKey, WEBAPI_URI_SCHEME_VAL schemeValue); 	// uri=KEY:VALUE
	CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, int contentId);					// uri=video|audio:content?contentId=CONTENTID
	CWebApiUriCreator(EN_FD_INPUT_TYPE inputType, ST_TRIPLET_INFO& triplet);				// uri=tv:isdbt|isdbbs|isdbcs?trip=TRIPLET
	CWebApiUriCreator(EN_FD_CAS_TYPE casType, ST_TRIPLET_INFO& triplet);				// uri=tv:isdbt|isdbbs|isdbcs?trip=TRIPLET
	CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet);			// uri=tv:isdbt|isdbbs|isdbcs?trip=TRIPLET
	CWebApiUriCreator(WEBAPI_URI_STORAGE_TYPE storageType);									// uri=storage:STORAGE_TYPE
	CWebApiUriCreator(WEBAPI_URI_SOURCE_TYPE sourceType, CTitleId& cTitleId);				// uri = video:content?contentId=aaaa&storageType=bbbb&titleType=cccc&streamType=dddd&folderType=eeee
	virtual ~CWebApiUriCreator();

public:
	void createScheme(WEBAPI_URI_SCHEME_KEY schemeKey, WEBAPI_URI_SCHEME_VAL schemeValue);
	void createTriplet(EN_FD_INPUT_TYPE inputType, ST_TRIPLET_INFO& triplet);
	void createTriplet(EN_FD_CAS_TYPE casType, ST_TRIPLET_INFO& triplet);
	void createStorage(WEBAPI_URI_STORAGE_TYPE storageType);

	void addParam(WEBAPI_URI_PARAM_TYPE paramType, const char* paramValue);
	void addParam(WEBAPI_URI_PARAM_TYPE paramType, int paramValueInt);
	void addContentId(const char* contentId);
	void addContentId(int contentId);
	void addStorageType(WEBAPI_URI_STORAGE_TYPE storageType);
	void addTitleType(TTL_TYPE titleType);
	void addStreamType(TTL_STRM streamType);
	void addFolderType(Ushort folderType);
	void addTitleNo(int titleNo);
	void addTriplet(ST_TRIPLET_INFO& triplet);
	void addTitlePathName(const char* titleName);
	void addTitlePathId(int titleId);
	void addRecordingTypePathId(int titleId);
	void addAlbumPathId(int albumId);
	void addArtistPathId(int artistId);
	void addIndex(int index);
	void addTitleId(CTitleId& cTitleId);
	void addUuid(const char* uuid);

	const char* getUri() { return m_uri; }

	static WEBAPI_URI_STORAGE_TYPE getStorageType(WEBAPI_URI_SOURCE_TYPE sourceType);
	static WEBAPI_URI_STORAGE_TYPE getStorageType(EN_CMH_DRIVE driveType);
	static WEBAPI_URI_STORAGE_TYPE getStorageType(EN_CMH_MEDIA_TYPE mediaType);

private:
	void appendUri(const char* str);
	bool isEqual(const char* str1, const char* str2);
	bool isMatch(const char* str1, const char* str2);

private:
	void init()
	{
		m_isFirstParam = true;
		memset(m_uri, 0, sizeof(m_uri));
	}

private:
	char					m_uri[WEBAPI_URI_STRING_MAX + 1];
	bool					m_isFirstParam;
};

/*-----------------------------------------------------------
 CWebApiThumbnailUrlCreator
-----------------------------------------------------------*/
enum THUMBNAIL_ICON_TYPE {
	THUMBNAIL_ICON_TYPE_HD,
	THUMBNAIL_ICON_TYPE_SD,
};
class CWebApiThumbnailUrlCreator
{
public:
	CWebApiThumbnailUrlCreator(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId);
	CWebApiThumbnailUrlCreator(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet, THUMBNAIL_ICON_TYPE type);
	CWebApiThumbnailUrlCreator(const char* uuid, WEBAPI_URI_STORAGE_TYPE storageType, Uint32 uniqueId);
	virtual ~CWebApiThumbnailUrlCreator();

public:
	const char* getUrl() { return m_thumbnailUrl; }

private:
	void createThumbnail(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId);
	void createIcon(WEBAPI_URI_SOURCE_TYPE sourceType, ST_TRIPLET_INFO& triplet, THUMBNAIL_ICON_TYPE type);
	void createHousemoving(const char* uuid, WEBAPI_URI_STORAGE_TYPE storageType, Uint32 uniqueId);

private:
	CWebApiThumbnailUrlCreator()
		: m_thumbnailUrl()
	{}
	void init()
	{
		memset(m_thumbnailUrl, 0, sizeof(m_thumbnailUrl));
	}

	bool isEqual(const char* str1, const char* str2);
	bool isMatch(const char* str1, const char* str2);

private:
	char					m_thumbnailUrl[WEBAPI_URI_STRING_MAX + 1];
};

/*-----------------------------------------------------------
 CWebApiPathCreator
-----------------------------------------------------------*/
class CWebApiPathCreator
{
public:
	static CWebApiPathCreator CreateThumbnailPath(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId);

public:
	const char* getPath() { return m_thumbnailUrl; }

private:
	void createThumbnail(WEBAPI_URI_SOURCE_TYPE sourceType, UINT32 uniqueId);

public:
	CWebApiPathCreator()
		: m_thumbnailUrl()
	{}
	virtual ~CWebApiPathCreator()
	{}

private:
	char					m_thumbnailUrl[WEBAPI_URI_STRING_MAX + 1];
};

#endif /* __WEBAPI_URI_H__ */
