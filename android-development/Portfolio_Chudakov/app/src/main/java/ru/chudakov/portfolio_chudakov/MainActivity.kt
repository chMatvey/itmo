package ru.chudakov.portfolio_chudakov

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import com.mikepenz.materialdrawer.AccountHeaderBuilder
import com.mikepenz.materialdrawer.DrawerBuilder
import com.mikepenz.materialdrawer.model.DividerDrawerItem
import com.mikepenz.materialdrawer.model.PrimaryDrawerItem
import com.mikepenz.materialdrawer.model.SecondaryDrawerItem
import kotlinx.android.synthetic.main.app_bar_main.*
import ru.chudakov.portfolio_chudakov.aboutMe.AboutMeFragment
import ru.chudakov.portfolio_chudakov.contacts.ContactsFragment
import ru.chudakov.portfolio_chudakov.job.JobFragment
import ru.chudakov.portfolio_chudakov.plans.PlansFragment
import ru.chudakov.portfolio_chudakov.studing.StudyFragment

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val header = AccountHeaderBuilder()
            .withActivity(this)
            .withHeaderBackground(R.drawable.cat)
            .build()

        val aboutMeItem = PrimaryDrawerItem().withName(R.string.about_me)
        val studyItem = PrimaryDrawerItem().withName(R.string.study)
        val jobItem = PrimaryDrawerItem().withName(R.string.job)
        val plansItem = PrimaryDrawerItem().withName(R.string.plans)
        val contactsItem = SecondaryDrawerItem().withName(R.string.contacts)

        val aboutMeFragment = AboutMeFragment()
        val studyFragment = StudyFragment()
        val jobFragment = JobFragment()
        val plansFragment = PlansFragment()
        val contactsFragment = ContactsFragment()

        changeFragment(aboutMeFragment)

        DrawerBuilder()
            .withActivity(this)
            .withToolbar(toolBar)
            .withAccountHeader(header)
            .addDrawerItems(
                aboutMeItem,
                studyItem,
                jobItem,
                plansItem,
                DividerDrawerItem(),
                contactsItem
            )
            .withOnDrawerItemClickListener { _, position, _ ->
                var result = false;

                when (position) {
                    1 -> changeFragment(aboutMeFragment)
                    2 -> changeFragment(studyFragment)
                    3 -> changeFragment(jobFragment)
                    4 -> changeFragment(plansFragment)
                    6 -> changeFragment(contactsFragment)
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
