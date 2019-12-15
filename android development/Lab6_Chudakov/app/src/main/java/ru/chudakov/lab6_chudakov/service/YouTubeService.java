package ru.chudakov.lab6_chudakov.service;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;
import ru.chudakov.lab6_chudakov.dto.PlaylistDTO;

public interface YouTubeService {
    String YOUTUBE_SEARCH_BASE_URL = "https://www.googleapis.com/youtube/v3/";

    @GET("playlistItems?part=snippet&maxResults=50")
    Call<PlaylistDTO> getPlaylistById(@Query("key") String key, @Query("playlistId") String playlistId);
}
