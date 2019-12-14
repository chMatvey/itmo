package ru.chudakov.lab6_chudakov;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;

import android.os.Bundle;
import android.view.View;

import com.mikepenz.fontawesome_typeface_library.FontAwesome;
import com.mikepenz.materialdrawer.Drawer;
import com.mikepenz.materialdrawer.DrawerBuilder;
import com.mikepenz.materialdrawer.model.DividerDrawerItem;
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem;
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem;
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem;

import ru.chudakov.lab6_chudakov.home.HomeFragment;
import ru.chudakov.lab6_chudakov.info.InfoFragment;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.tool_bar);

        final PrimaryDrawerItem home = new PrimaryDrawerItem().withName(R.string.menu_home);
        final PrimaryDrawerItem info = new PrimaryDrawerItem().withName(R.string.menu_info);

        final Fragment homeFragment = new HomeFragment();
        final Fragment infoFragment = new InfoFragment();

        changeFragment(homeFragment);

        new DrawerBuilder()
                .withActivity(this)
                .withToolbar(toolbar)
                .addDrawerItems(
                        home
                )
                .withOnDrawerItemClickListener(new Drawer.OnDrawerItemClickListener() {
                    @Override
                    public boolean onItemClick(View view, int position, IDrawerItem drawerItem) {
                        Fragment fragment;

                        switch (position) {
                            case 0: {
                                fragment = homeFragment;
                                break;
                            }
                            case 1: {
                                fragment = homeFragment;
                                break;
                            }
                            case 3: {
                                fragment = homeFragment;
                                break;
                            }
                            case 4: {
                                fragment = infoFragment;
                                break;
                            }
                            default: {
                                return true;
                            }
                        }
                        changeFragment(fragment);

                        return false;
                    }
                })
                .build();
    }

    private void changeFragment(Fragment fragment) {
        getSupportFragmentManager()
                .beginTransaction()
                .replace(R.id.container, fragment)
                .commit();
    }
}
