package ru.chudakov.portfolio_chudakov.studing

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import kotlinx.android.synthetic.main.app_bar_main.view.*
import ru.chudakov.portfolio_chudakov.R

class StudyFragment : Fragment() {
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        inflater.inflate(R.layout.app_bar_main, container, false).toolbarTitle.setText(R.string.study)

        return inflater.inflate(R.layout.fragment_study, container, false)
    }
}