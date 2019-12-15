package ru.chudakov.portfolio_chudakov.aboutMe

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import kotlinx.android.synthetic.main.app_bar_main.view.*
import ru.chudakov.portfolio_chudakov.R

class AboutMeFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        inflater.inflate(R.layout.app_bar_main, container, false).toolbarTitle.setText(R.string.about_me)

        return inflater.inflate(R.layout.fragment_about_me, container, false)
    }
}