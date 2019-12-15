package ru.chudakov.lab5_chudakov.recycler;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.StaggeredGridLayoutManager;

import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

import ru.chudakov.lab5_chudakov.R;
import ru.chudakov.lab5_chudakov.recycler.adapter.ListAdapter;
import ru.chudakov.lab5_chudakov.recycler.pojo.Person;

public class RecyclerFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        TextView title = ((AppCompatActivity) Objects.requireNonNull(getActivity())).findViewById(R.id.toolbar_title);
        title.setText(R.string.menu_recycler_view);

        View root = inflater.inflate(R.layout.fragment_recycler, container, false);

        RecyclerView.Adapter adapter = new ListAdapter(getPersons());

        RecyclerView recyclerView = root.findViewById(R.id.recyclerView);
        RecyclerView.LayoutManager layoutManager = new StaggeredGridLayoutManager(1,1);
        recyclerView.setLayoutManager(layoutManager);
        recyclerView.setAdapter(adapter);

        return root;
    }

    private List<Person> getPersons() {
        List<Person> result = new LinkedList<>();

        result.add(new Person(
                "Mikhail Lomonosov",
                R.drawable.lomonosov,
                "Russia"
        ));
        result.add(new Person(
                "Nikola Tesla",
                R.drawable.tesla,
                "USA"
        ));
        result.add(new Person(
                "Albert Einstein",
                R.drawable.einstein,
                "Germany"
        ));
        result.add(new Person(
                "Dmitri Mendeleev",
                R.drawable.mendeleev,
                "Russia"
                )
        );

        return result;
    }
}
