package ru.chudakov.lab5_chudakov.bitcoin;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import java.util.Objects;

import ru.chudakov.lab5_chudakov.R;

public class BitcoinFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        TextView title = ((AppCompatActivity) Objects.requireNonNull(getActivity())).findViewById(R.id.toolbar_title);
        title.setText(R.string.menu_bitcoin);

        return inflater.inflate(R.layout.fragment_bitcoin, container, false);
    }
}
