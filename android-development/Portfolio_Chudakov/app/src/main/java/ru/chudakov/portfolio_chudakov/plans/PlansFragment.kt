package ru.chudakov.portfolio_chudakov.plans

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import ru.chudakov.portfolio_chudakov.R

class PlansFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        activity?.findViewById<TextView>(R.id.toolbarTitle)?.setText(R.string.plans)

        return inflater.inflate(R.layout.fragment_plans, container, false)
    }
}