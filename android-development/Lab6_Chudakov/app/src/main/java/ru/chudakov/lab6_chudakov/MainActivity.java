package ru.chudakov.lab6_chudakov;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;

import com.mikepenz.materialdrawer.AccountHeader;
import com.mikepenz.materialdrawer.AccountHeaderBuilder;
import com.mikepenz.materialdrawer.Drawer;
import com.mikepenz.materialdrawer.DrawerBuilder;
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem;
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import ru.chudakov.lab6_chudakov.home.HomeFragment;
import ru.chudakov.lab6_chudakov.info.InfoFragment;
import ru.chudakov.lab6_chudakov.playlist.PlaylistFragment;
import ru.chudakov.lab6_chudakov.service.YouTubeService;

import static ru.chudakov.lab6_chudakov.config.YouTubeConfig.androidDeveloperStories;
import static ru.chudakov.lab6_chudakov.config.YouTubeConfig.androidDevelopmentPatternsId;
import static ru.chudakov.lab6_chudakov.config.YouTubeConfig.androidStudioFeaturesId;
import static ru.chudakov.lab6_chudakov.playlist.PlaylistFragment.newInstance;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final Toolbar toolbar = findViewById(R.id.tool_bar);

        final AccountHeader header = new AccountHeaderBuilder()
                .withActivity(this)
                .withHeaderBackground(R.drawable.cat)
                .build();

        final PrimaryDrawerItem homeItem = new PrimaryDrawerItem().withName(R.string.menu_home);
        final PrimaryDrawerItem playlistFeaturesItem = new PrimaryDrawerItem().withName(R.string.menu_playlist_features);
        final PrimaryDrawerItem playlistPatternsItem = new PrimaryDrawerItem().withName(R.string.menu_playlist_patterns);
        final PrimaryDrawerItem playlistStoriesItem = new PrimaryDrawerItem().withName(R.string.menu_playlist_stories);
        final PrimaryDrawerItem infoItem = new PrimaryDrawerItem().withName(R.string.menu_info);

        final Fragment homeFragment = new HomeFragment();
        final Fragment playlistFeaturesFragment = newInstance(androidStudioFeaturesId, R.string.features);
        final Fragment playlistPatternsFragment = newInstance(androidDevelopmentPatternsId, R.string.patterns);
        final Fragment playlistStoriesFragment = newInstance(androidDeveloperStories, R.string.stories);
        final Fragment infoFragment = new InfoFragment();

        changeFragment(homeFragment);

        new DrawerBuilder()
                .withActivity(this)
                .withAccountHeader(header)
                .withToolbar(toolbar)
                .addDrawerItems(
                        homeItem,
                        playlistFeaturesItem,
                        playlistPatternsItem,
                        playlistStoriesItem,
                        infoItem
                )
                .withOnDrawerItemClickListener(new Drawer.OnDrawerItemClickListener() {
                    @Override
                    public boolean onItemClick(View view, int position, IDrawerItem drawerItem) {
                        Fragment fragment;

                        switch (position) {
                            case 0:
                            case 1: {
                                fragment = homeFragment;
                                break;
                            }
                            case 2: {
                                fragment = playlistFeaturesFragment;
                                break;
                            }
                            case 3: {
                                fragment = playlistPatternsFragment;
                                break;
                            }
                            case 4: {
                                fragment = playlistStoriesFragment;
                                break;
                            }
                            case 5: {
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
