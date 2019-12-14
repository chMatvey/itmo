package ru.chudakov.lab6_chudakov.service;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;
import ru.chudakov.lab6_chudakov.config.YouTubeConfig;
import ru.chudakov.lab6_chudakov.pojo.Playlist;

public interface YouTubeService {
    String YOUTUBE_SEARCH_BASE_URL = "https://www.googleapis.com/youtube/v3/";

    @GET("playlistItems?part=snippet&maxResults=50&key=" + YouTubeConfig.YOUTUBE_API_KEY)
    Call<Playlist> getPlaylistById(@Query("playlistId") String playlistId);
}
