# steamavatarchanger

This program automatically changes your steam avatar. http://i.imgur.com/4qUCv8A.gifv

It works by sending post requests to the uploading page ( http://steamcommunity.com/actions/FileUploader?type=player_avatar_image&sId=yoursteamid64&bgColor=262627 )

It requires your steamid64, sessionid, and steam cookie. To get those you can go to the uploading page, and view the uploading pages source. The steam cookie can be acquired through your browser. Its exact name is "SteamLogin".


FAQ:
Q: Can I use anything else than .gif?
A: Yes.

Q: VCRUNTIME140.dll is missing, what should I do?
A: Download this https://www.microsoft.com/de-de/downl...

Q: It keeps saying no file found lol
A: Then you didn't write e.g. "*.gif" but ".gif" instead. The * is important. Otherwise, you don't have any images matching the pattern in that directory.

Q: I don't have the cookie, is this broken?
A: No it's not, you need to log in and stay logged in.

Q: How many frames can this have?
A: As much as you want.

Q: Does this harm the steam servers in any way?
A: No, only few bytes are sent per second. Millions of users request and send data to steam every day. Think of it the same way as browsing steam.

Q: Is this an exploit?
A: No.

Q: Does this bypass steams file uploading checks?
A: No.
