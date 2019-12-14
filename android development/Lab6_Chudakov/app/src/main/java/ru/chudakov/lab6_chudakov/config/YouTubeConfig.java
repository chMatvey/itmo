package ru.chudakov.lab6_chudakov.config;

public final class YouTubeConfig {
    private YouTubeConfig() {
    }

    public static final String YOUTUBE_API_KEY = System.getenv("YOUTUBE_API_KEY");
}
