package ru.chudakov.portfolio_chudakov.studing

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.fragment_study.view.*
import ru.chudakov.portfolio_chudakov.R
import ru.chudakov.portfolio_chudakov.studing.adapter.StudyAdapter
import ru.chudakov.portfolio_chudakov.studing.pojo.Institution

class StudyFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        activity?.findViewById<TextView>(R.id.toolbarTitle)?.setText(R.string.study)

        val root = inflater.inflate(R.layout.fragment_study, container, false)

        root.studyList.layoutManager = LinearLayoutManager(context)
        root.studyList.adapter = StudyAdapter(getInstitution())

        return root
    }

    private fun getInstitution(): List<Institution> {
        return listOf(
            Institution(R.drawable.lyceum,"Лицей №1, город Кунгур", "2009 - 2016", "Физико-математический класс"),
            Institution(R.drawable.itmo, "Университет ИТМО", "2016 - 2020", "Программная инженерия"),
            Institution(R.drawable.itmo, "Университет ИТМО, военная кафедра", "2018 - 2021", "Эксплуатация и ремонт корабельных комплексов крылатых ракет")
        )
    }
}