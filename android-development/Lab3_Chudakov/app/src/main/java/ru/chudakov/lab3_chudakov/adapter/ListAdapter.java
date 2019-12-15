package ru.chudakov.lab3_chudakov.adapter;

import android.media.MediaPlayer;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.squareup.picasso.Picasso;
import com.squareup.picasso.RequestCreator;

import java.io.IOException;
import java.util.List;

import ru.chudakov.lab3_chudakov.R;
import ru.chudakov.lab3_chudakov.pojo.Item;

public class ListAdapter extends RecyclerView.Adapter<ListAdapter.ListHolder>  {

    private List<Item> items;

    private MediaPlayer mediaPlayer;

    public ListAdapter(List<Item> items, MediaPlayer mediaPlayer) {
        this.items = items;
        this.mediaPlayer = mediaPlayer;
    }

    @NonNull
    @Override
    public ListHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View itemView = inflater.inflate(R.layout.activity_main, parent, false);

        return new ListHolder(itemView, mediaPlayer);
    }

    @Override
    public void onBindViewHolder(@NonNull ListHolder listHolder, int i) {
        Item itemList = items.get(i);
        RequestCreator req = Picasso.get().load(itemList.getImageSrc());
        req.into(listHolder.image);
    }

    @Override
    public int getItemCount() {
        return items.size();
    }

    static class ListHolder extends RecyclerView.ViewHolder {

        public final ImageView image;

        public ListHolder(@NonNull View itemView, @NonNull final MediaPlayer mediaPlayer) {
            super(itemView);

            image = itemView.findViewById(R.id.item_list);
            image.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mediaPlayer.isPlaying()) {
                        mediaPlayer.stop();
                        try {
                            mediaPlayer.prepare();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                    mediaPlayer.start();
                }
            });
        }
    }
}
