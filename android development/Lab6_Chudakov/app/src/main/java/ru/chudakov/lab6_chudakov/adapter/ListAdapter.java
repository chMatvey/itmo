package ru.chudakov.lab6_chudakov.adapter;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.youtube.player.YouTubeInitializationResult;
import com.google.android.youtube.player.YouTubeStandalonePlayer;
import com.google.android.youtube.player.YouTubeThumbnailLoader;
import com.google.android.youtube.player.YouTubeThumbnailView;

import java.util.Objects;

import ru.chudakov.lab6_chudakov.R;
import ru.chudakov.lab6_chudakov.config.YouTubeConfig;
import ru.chudakov.lab6_chudakov.dto.PlaylistDTO;
import ru.chudakov.lab6_chudakov.dto.SnippetDTO;

public class ListAdapter extends RecyclerView.Adapter<ListAdapter.VideoInfoHolder> {

    private PlaylistDTO playlist;

    public ListAdapter(PlaylistDTO playlist) {
        this.playlist = playlist;
    }

    @NonNull
    @Override
    public VideoInfoHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.activity_row, parent, false);

        return new VideoInfoHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull VideoInfoHolder holder, int position) {
        final SnippetDTO snippet = playlist.getItems().get(position).getSnippet();
        holder.setVideoId(snippet.getResourceId().getVideoId());
        holder.title.setText(snippet.getTitle());

        final YouTubeThumbnailLoader.OnThumbnailLoadedListener onThumbnailLoadedListener = new YouTubeThumbnailLoader.OnThumbnailLoadedListener() {
            @Override
            public void onThumbnailLoaded(YouTubeThumbnailView youTubeThumbnailView, String s) {
                youTubeThumbnailView.setVisibility(View.VISIBLE);
            }

            @Override
            public void onThumbnailError(YouTubeThumbnailView youTubeThumbnailView, YouTubeThumbnailLoader.ErrorReason errorReason) {
            }
        };

        holder.youTubeThumbnailView.initialize(YouTubeConfig.YOUTUBE_API_KEY, new YouTubeThumbnailView.OnInitializedListener() {
            @Override
            public void onInitializationSuccess(YouTubeThumbnailView youTubeThumbnailView, YouTubeThumbnailLoader youTubeThumbnailLoader) {
                youTubeThumbnailLoader.setVideo(snippet.getResourceId().getVideoId());
                youTubeThumbnailLoader.setOnThumbnailLoadedListener(onThumbnailLoadedListener);
            }

            @Override
            public void onInitializationFailure(YouTubeThumbnailView youTubeThumbnailView, YouTubeInitializationResult youTubeInitializationResult) {
            }
        });
    }

    @Override
    public int getItemCount() {
        return playlist.getItems().size();
    }

    static class VideoInfoHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private String videoId;

        private Context context;

        private TextView title;

        private YouTubeThumbnailView youTubeThumbnailView;

        public VideoInfoHolder(@NonNull View itemView) {
            super(itemView);

            context = itemView.getContext();
            title = itemView.findViewById(R.id.title);
            youTubeThumbnailView = itemView.findViewById(R.id.youtube_thumbnail);
            youTubeThumbnailView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            Intent intent = YouTubeStandalonePlayer.createVideoIntent(
                    (Activity) context,
                    Objects.requireNonNull(YouTubeConfig.YOUTUBE_API_KEY),
                    videoId,
                    0,
                    true,
                    true
            );

            context.startActivity(intent);
        }

        public void setVideoId(String videoId) {
            this.videoId = videoId;
        }
    }
}
