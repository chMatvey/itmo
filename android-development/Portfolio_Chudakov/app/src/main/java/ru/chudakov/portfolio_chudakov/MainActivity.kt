package ru.chudakov.portfolio_chudakov

import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import com.mikepenz.materialdrawer.Drawer
import com.mikepenz.materialdrawer.DrawerBuilder
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem
import com.mikepenz.materialdrawer.model.interfaces.IDrawerItem
import kotlinx.android.synthetic.main.app_bar_main.*
import ru.chudakov.portfolio_chudakov.aboutMe.AboutMeFragment
import ru.chudakov.portfolio_chudakov.studing.StudyFragment

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val aboutMeItem = PrimaryDrawerItem().withName(R.string.about_me)
        val studyItem = PrimaryDrawerItem().withName(R.string.study)

        val aboutMeFragment = AboutMeFragment()
        val studyFragment = StudyFragment()

        changeFragment(aboutMeFragment)

        DrawerBuilder()
            .withActivity(this)
            .withToolbar(toolBar)
            .addDrawerItems(
                aboutMeItem,
                studyItem
            )
            .withOnDrawerItemClickListener { _, position, _ ->
                var result = false;

                when (position) {
                    0 -> changeFragment(aboutMeFragment)
                    1 -> changeFragment(studyFragment)
                    else -> result = true;
                }

                result
            }
            .build()
    }

    private fun changeFragment(fragment: Fragment) {
        supportFragmentManager
            .beginTransaction()
            .replace(R.id.container, fragment)
            .commit()
    }
}
