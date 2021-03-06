#include "download.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int setupContext(httpcContext * context, const char * url, u32 * size)
{
	Result ret = 0;
	u32 statuscode = 0;
	
	ret = httpcOpenContext(context, HTTPC_METHOD_GET, url, 1);
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "User-Agent", "MultiUpdater");
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcSetSSLOpt(context, SSLCOPT_DisableVerify);
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcAddRequestHeaderField(context, "Connection", "Keep-Alive");
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcBeginRequest(context);
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	ret = httpcGetResponseStatusCode(context, &statuscode);
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	if ((statuscode >= 301 && statuscode <= 303) || (statuscode >= 307 && statuscode <= 308)) {
		char * newurl = malloc(0x1000); // One 4K page for new URL
		if (newurl == NULL) {
			httpcCloseContext(context);
			return 2;
		}
		
		ret = httpcGetResponseHeader(context, "Location", newurl, 0x1000);
		if (ret != 0) {
			httpcCloseContext(context);
			free(newurl);
			return ret;
		}
		
		httpcCloseContext(context); // Close this context before we try the next
		
		if (newurl[0] == '/') { //if the url starts with a slash, it's local
			int slashpos = 0;
			char * domainname = strdup(url);
			if (strncmp("http", domainname, 4) == 0) slashpos = 8; //if the url in the entry starts with http:// or https:// we need to skip that
			slashpos = strchr(domainname+slashpos, '/')-domainname;
			domainname[slashpos] = '\0'; // replace the slash with a nullbyte to cut the url
			char * copyurl = strdup(newurl);
			sprintf(newurl, "%s%s", domainname, copyurl);
			free(copyurl);
			free(domainname);
		}
		
		ret = setupContext(context, newurl, size);
		free(newurl);
		return ret;
	}
	
	if (statuscode != 200) {
		httpcCloseContext(context);
		return 3;
	}
	
	ret = httpcGetDownloadSizeState(context, NULL, size);
	if (ret != 0) {
		httpcCloseContext(context);
		return ret;
	}
	
	return 0;
}

int downloadToFile(const char * url, const char * filepath)
{
	if (url == NULL) {
		return 1;
	}
	
	if (filepath == NULL) {
		return 1;
	}
	
	httpcContext context;
	Result ret = 0;
	u32 contentsize = 0, readsize = 0;
	
	ret = setupContext(&context, url, &contentsize);
	if (ret != 0) return ret;
	
	FILE * fh = fopen(filepath, "wb");
	if (fh == NULL) {
		return 5;
	}
	
	u8 * buf = malloc(0x1000);
	if (buf == NULL) {
		httpcCloseContext(&context);
		return 3;
	}
	
	u64 startTime = osGetTime();
	do {
		ret = httpcDownloadData(&context, buf, 0x1000, &readsize);
		fwrite(buf, 1, readsize, fh);
	} while (ret == (Result)HTTPC_RESULTCODE_DOWNLOADPENDING);
	
	free(buf);
	fclose(fh);
	httpcCloseContext(&context);
	
	if (ret != 0) {
		return ret;
	}
	printf("\x1b[20;15HDownload Complete");
	return 0;
}
