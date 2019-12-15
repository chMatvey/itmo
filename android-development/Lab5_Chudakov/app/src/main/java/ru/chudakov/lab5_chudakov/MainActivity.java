package ru.chudakov.lab5_chudakov;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;

import com.mikepenz.fontawesome_typeface_library.FontAwesome;
import com.mikepenz.materialdrawer.Drawer;
import com.mikepenz.materialdrawer.DrawerBuilder;
import com.mikepenz.materialdrawer.model.DividerDrawerItem;
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem;
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem;
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem;

import ru.chudakov.lab5_chudakov.bitcoin.BitcoinFragment;
import ru.chudakov.lab5_chudakov.calendar.CalendarFragment;
import ru.chudakov.lab5_chudakov.cloud.CloudFragment;
import ru.chudakov.lab5_chudakov.github.GithubFragment;
import ru.chudakov.lab5_chudakov.home.HomeFragment;
import ru.chudakov.lab5_chudakov.recycler.RecyclerFragment;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.tool_bar);

        final PrimaryDrawerItem home = new PrimaryDrawerItem().withName(R.string.menu_home);
        final PrimaryDrawerItem recycler = new PrimaryDrawerItem().withName(R.string.menu_recycler_view);

        final SecondaryDrawerItem github = new SecondaryDrawerItem().withName(R.string.menu_github).withIcon(FontAwesome.Icon.faw_github);
        final SecondaryDrawerItem calendar = new SecondaryDrawerItem().withName(R.string.menu_calendar).withIcon(FontAwesome.Icon.faw_calendar);
        final SecondaryDrawerItem cloud = new SecondaryDrawerItem().withName(R.string.menu_cloud).withIcon(FontAwesome.Icon.faw_cloud);
        final SecondaryDrawerItem bitcoin = new SecondaryDrawerItem().withName(R.string.menu_bitcoin).withIcon(FontAwesome.Icon.faw_bitcoin);

        final HomeFragment homeFragment = new HomeFragment();
        final RecyclerFragment recyclerFragment = new RecyclerFragment();
        final GithubFragment githubFragment = new GithubFragment();
        final CalendarFragment calendarFragment = new CalendarFragment();
        final CloudFragment cloudFragment = new CloudFragment();
        final BitcoinFragment bitcoinFragment = new BitcoinFragment();

        changeFragment(homeFragment);

        new DrawerBuilder()
                .withActivity(this)
                .withToolbar(toolbar)
                .addDrawerItems(
                        home,
                        recycler,
                        new DividerDrawerItem(),
                        github,
                        calendar,
                        cloud,
                        bitcoin
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
                                fragment = recyclerFragment;
                                break;
                            }
                            case 3: {
                                fragment = githubFragment;
                                break;
                            }
                            case 4: {
                                fragment = calendarFragment;
                                break;
                            }
                            case 5: {
                                fragment = cloudFragment;
                                break;
                            }
                            case 6: {
                                fragment = bitcoinFragment;
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
