package ru.chudakov.lab5_chudakov;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.os.Bundle;
import android.view.View;

import com.mikepenz.fontawesome_typeface_library.FontAwesome;
import com.mikepenz.materialdrawer.Drawer;
import com.mikepenz.materialdrawer.DrawerBuilder;
import com.mikepenz.materialdrawer.model.DividerDrawerItem;
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem;
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem;
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem;

import ru.chudakov.lab5_chudakov.home.HomeFragment;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.tool_bar);
        setSupportActionBar(toolbar);

        PrimaryDrawerItem home = new PrimaryDrawerItem().withName(R.string.menu_home);
        SecondaryDrawerItem card = new SecondaryDrawerItem().withName(R.string.menu_card_view);
        SecondaryDrawerItem recycler = new SecondaryDrawerItem().withName(R.string.menu_recycler_view);
        SecondaryDrawerItem github = new SecondaryDrawerItem().withName(R.string.menu_github).withIcon(FontAwesome.Icon.faw_github);

        final HomeFragment homeFragment = new HomeFragment();

        new DrawerBuilder()
                .withActivity(this)
                .withToolbar(toolbar)
                .addDrawerItems(
                        home,
                        new DividerDrawerItem(),
                        card,
                        recycler,
                        github
                )
                .withOnDrawerItemClickListener(new Drawer.OnDrawerItemClickListener() {
                    @Override
                    public boolean onItemClick(View view, int position, IDrawerItem drawerItem) {
                        getSupportFragmentManager()
                                .beginTransaction()
                                .replace(R.id.container, homeFragment)
                                .commit();
                        return false;
                    }
                })
                .build();
    }
}
