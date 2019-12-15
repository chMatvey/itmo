package ru.chudakov.lab6_chudakov.playlist;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import java.util.Objects;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import ru.chudakov.lab6_chudakov.R;
import ru.chudakov.lab6_chudakov.adapter.ListAdapter;
import ru.chudakov.lab6_chudakov.dto.PlaylistDTO;
import ru.chudakov.lab6_chudakov.service.YouTubeService;

import static ru.chudakov.lab6_chudakov.config.YouTubeConfig.YOUTUBE_API_KEY;

public class PlaylistFragment extends Fragment {
    private String playlistId;

    private int titleId;

    private YouTubeService youTubeService;

    private RecyclerView recyclerView;

    private SwipeRefreshLayout swipeRefreshLayout;

    private AlertDialog.Builder alertBuilder;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        Bundle args = getArguments();
        playlistId = Objects.requireNonNull(args).getString("playlistId");
        titleId = Objects.requireNonNull(args).getInt("titleId");

        TextView title = ((AppCompatActivity) Objects.requireNonNull(getActivity())).findViewById(R.id.toolbar_title);
        title.setText(titleId);

        View root = inflater.inflate(R.layout.fragment_playlist, container, false);

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(YouTubeService.YOUTUBE_SEARCH_BASE_URL)
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        youTubeService = retrofit.create(YouTubeService.class);

        LinearLayoutManager linearLayoutManager = new LinearLayoutManager(getContext());
        linearLayoutManager.setOrientation(LinearLayoutManager.VERTICAL);

        alertBuilder = new AlertDialog.Builder(root.getContext());
        alertBuilder.setTitle("Videos upload error\n")
                .setCancelable(false)
                .setNegativeButton("OK",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

        recyclerView = root.findViewById(R.id.recyclerView);
        recyclerView.setHasFixedSize(true);
        recyclerView.setItemViewCacheSize(50);
        recyclerView.setDrawingCacheEnabled(true);
        recyclerView.setDrawingCacheQuality(View.DRAWING_CACHE_QUALITY_HIGH);
        recyclerView.setLayoutManager(linearLayoutManager);

        swipeRefreshLayout = root.findViewById(R.id.swipe);

        swipeRefreshLayout.setRefreshing(true);
        swipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                getPlaylist();
            }
        });
        getPlaylist();

        return root;
    }

    private void getPlaylist() {
        Call<PlaylistDTO> searchCall = youTubeService.getPlaylistById(YOUTUBE_API_KEY, playlistId);
        searchCall.enqueue(new Callback<PlaylistDTO>() {
            @Override
            public void onResponse(Call<PlaylistDTO> call, Response<PlaylistDTO> response) {
                PlaylistDTO playlist = response.body();
                ListAdapter adapter = new ListAdapter(playlist);
                recyclerView.setAdapter(adapter);
                swipeRefreshLayout.setRefreshing(false);
            }

            @Override
            public void onFailure(Call<PlaylistDTO> call, Throwable t) {
                swipeRefreshLayout.setRefreshing(false);
                alertBuilder.setMessage(t.getMessage());
                AlertDialog alert = alertBuilder.create();
                alert.show();
            }
        });
    }

    public static PlaylistFragment newInstance(String playlistId, int titleId) {
        Bundle args = new Bundle();
        args.putString("playlistId", playlistId);
        args.putInt("titleId", titleId);
        PlaylistFragment fragment = new PlaylistFragment();
        fragment.setArguments(args);

        return fragment;
    }
}
