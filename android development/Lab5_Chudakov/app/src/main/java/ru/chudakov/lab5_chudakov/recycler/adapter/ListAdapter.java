package ru.chudakov.lab5_chudakov.recycler.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

import ru.chudakov.lab5_chudakov.R;
import ru.chudakov.lab5_chudakov.recycler.pojo.Person;

public class ListAdapter extends RecyclerView.Adapter<ListAdapter.ListHolder> {

    private List<Person> persons;

    public ListAdapter(List<Person> persons) {
        this.persons = persons;
    }

    @NonNull
    @Override
    public ListHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View itemView = inflater.inflate(R.layout.fragment_recycler, parent, false);

        return new ListHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull final ListHolder listHolder, final int i) {
        Person person = persons.get(i);

        listHolder.image.setImageResource(person.getPhotoId());
        listHolder.textName.setText(person.getName());
        listHolder.textNationality.setText(person.getNationality());
    }

    @Override
    public int getItemCount() {
        return persons.size();
    }

    static class ListHolder extends RecyclerView.ViewHolder {

        private final ImageView image;

        private final TextView textName;

        private final TextView textNationality;

        private ListHolder(@NonNull View itemView) {
            super(itemView);

            image = itemView.findViewById(R.id.person_photo);
            textName = itemView.findViewById(R.id.person_name);
            textNationality = itemView.findViewById(R.id.person_nationality);
        }
    }
}
