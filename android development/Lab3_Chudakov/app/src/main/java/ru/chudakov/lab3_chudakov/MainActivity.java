package ru.chudakov.lab3_chudakov;

import android.media.MediaPlayer;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.StaggeredGridLayoutManager;

import java.util.ArrayList;
import java.util.List;

import ru.chudakov.lab3_chudakov.adapter.ListAdapter;
import ru.chudakov.lab3_chudakov.pojo.Item;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initRecyclerView();
    }

    private void initRecyclerView() {
        RecyclerView recyclerView = findViewById(R.id.recyclerView);
        RecyclerView.LayoutManager layoutManager = new StaggeredGridLayoutManager(2,1);
        recyclerView.setLayoutManager(layoutManager);

        MediaPlayer mediaPlayer = MediaPlayer.create(this, R.raw.sound);

        RecyclerView.Adapter adapter = new ListAdapter(generatedItem(), mediaPlayer);
        recyclerView.setAdapter(adapter);
    }

    private List<Item> generatedItem() {
        List<Item> itemLists = new ArrayList<>();

        itemLists.add(new Item("https://i.imgur.com/2KxoIsa.jpg"));
        itemLists.add(new Item("https://i.imgur.com/EZHXbA0.jpg"));
        itemLists.add(new Item("https://i.imgur.com/qb7Ev7A.jpg"));
        itemLists.add(new Item("https://i.imgur.com/ZtXXAwX.jpg"));
        itemLists.add(new Item("https://i.imgur.com/lrE9vha.jpg"));
        itemLists.add(new Item("https://i.imgur.com/S66rx9n.jpg"));
        itemLists.add(new Item("https://i.imgur.com/KaSkWef.jpg"));
        itemLists.add(new Item("https://i.imgur.com/jp5z1s0.jpg"));
        itemLists.add(new Item("https://i.imgur.com/iLNrl9Z.jpg"));
        itemLists.add(new Item("https://i.imgur.com/Z3ei74h.jpg"));
        itemLists.add(new Item("https://i.imgur.com/uXbb81d.jpg"));
        itemLists.add(new Item("https://i.imgur.com/92mT0BB.jpg"));

        return itemLists;
    }
}
