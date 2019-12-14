package ru.chudakov.lab6_chudakov.playlist.adapter;

import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class ListAdapter extends RecyclerView.Adapter<ListAdapter.VideoInfoHolder> {

    @NonNull
    @Override
    public VideoInfoHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return null;
    }

    @Override
    public void onBindViewHolder(@NonNull VideoInfoHolder holder, int position) {

    }

    @Override
    public int getItemCount() {
        return 0;
    }

    public class VideoInfoHolder extends RecyclerView.ViewHolder implements View.OnClickListener  {

        public VideoInfoHolder(@NonNull View itemView) {
            super(itemView);
        }

        @Override
        public void onClick(View view) {

        }
    }
}
