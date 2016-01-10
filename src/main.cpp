
#pragma once
#include "defines.h"
#include "curl/curl.h"

#include <math.h>

char steamid64[250];
char sessionid[250];
char steamlogin[250];

char cookie[600];

char*files[0xFFFF];

struct curl_httppost *formpost[0xFFFF];

void ChangeAvatar(int filenum)
{
	static CURL *curl = curl_easy_init();
	/*if (!curl)
	{
		printf("No curl!\n");
	}/*/

	curl_easy_setopt(curl, CURLOPT_URL, "http://steamcommunity.com/actions/FileUploader");
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
	curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);

	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);


	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost[filenum]);

	CURLcode res = curl_easy_perform(curl);

}

void addpostfile(const char*postfile, int num)
{
	struct curl_httppost *lastptr = NULL;

	curl_formadd(&formpost[num],
		&lastptr,
		CURLFORM_COPYNAME, "type",
		CURLFORM_COPYCONTENTS, "player_avatar_image",
		CURLFORM_END);

	curl_formadd(&formpost[num],
		&lastptr,
		CURLFORM_COPYNAME, "sId",
		CURLFORM_COPYCONTENTS, steamid64,
		CURLFORM_END);

	curl_formadd(&formpost[num],
		&lastptr,
		CURLFORM_COPYNAME, "sessionid",
		CURLFORM_COPYCONTENTS, sessionid,
		CURLFORM_END);


	curl_formadd(&formpost[num],
		&lastptr,
		CURLFORM_COPYNAME, "doSub",
		CURLFORM_COPYCONTENTS, "1",
		CURLFORM_END);


	curl_formadd(&formpost[num],
		&lastptr,
		CURLFORM_COPYNAME, "avatar",
		CURLFORM_FILE, postfile,
		CURLFORM_END);
}

int main(int argc, char** argv)
{

	curl_global_init(CURL_GLOBAL_ALL);

	if (!argv[1]||!argv[2]||!argv[3]||!argv[4])
	{
		printf("Args: \"files\" \"steamid64\" \"sessionid\" \"steamlogin\"\n");
		printf("Ex: \"C:/dickpics/*.gif\" \"776561198162962704\" \"7ba24g35f078968b1aaa78da19\" \"76561198162962704KD25AD16KK2GH7A482DKA6DK4AD2KG\"\n");
		getchar();
		return 0;
	}

	HWND previousinstance = FindWindow(0, "Steam Avatar Changer");

	if (previousinstance)
	{
		ExitProcess(0);
	}

	SetWindowText(GetForegroundWindow(), "Steam Avatar Changer");

	strcpy(steamid64, argv[2]);
	strcpy(sessionid, argv[3]);
	strcpy(steamlogin, argv[4]);

	printf("Location: %s\nSteamID64: %s\nSessionID: %s\nSteamLogin: %s\n\n\n", argv[1], argv[2], argv[3], argv[4]);


	sprintf(cookie, "sessionid=%s; steamLogin=%s", sessionid, steamlogin);

	WIN32_FIND_DATA data;

	void*file = FindFirstFile(argv[1], &data);

	if (file == INVALID_HANDLE_VALUE)
	{
		printf("No files found!\n");
		getchar();
		return 0;
	}



	int files_num = 0;

	files[files_num] = new char[strlen(data.cFileName) + 1];
	strcpy(files[files_num], data.cFileName);


	addpostfile(data.cFileName, files_num);
	files_num++;

	while (FindNextFile(file, &data))
	{
		files[files_num] = new char[strlen(data.cFileName) + 1];
		strcpy(files[files_num], data.cFileName);



		addpostfile(data.cFileName, files_num);



		files_num++;

		if (files_num > 0xFFF)
			break;
	}


	FindClose(file);


	int i = 0;
	int lasttime = 0;

	while (true)
	{



		if (!files[i])
		{
			i = 0;
			continue;
		}

		printf("Changing avatar to: %s\n", files[i]);
		ChangeAvatar(i);


		i++;
		Sleep(500);

	}

	return 0;
}