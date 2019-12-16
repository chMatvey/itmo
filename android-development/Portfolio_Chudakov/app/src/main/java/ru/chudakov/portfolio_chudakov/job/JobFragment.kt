package ru.chudakov.portfolio_chudakov.job

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.fragment_job.view.*
import ru.chudakov.portfolio_chudakov.R
import ru.chudakov.portfolio_chudakov.job.adapter.JobAdapter
import ru.chudakov.portfolio_chudakov.job.pojo.Job

class JobFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        activity?.findViewById<TextView>(R.id.toolbarTitle)?.setText(R.string.job)

        val root = inflater.inflate(R.layout.fragment_job, container, false)

        root.jobList.layoutManager = LinearLayoutManager(context)
        root.jobList.adapter = JobAdapter(getJobs())

        return root
    }

    private fun getJobs(): List<Job> {
        return listOf(
            Job(R.drawable.arcadia, "АО “Аркадия”", "2019-...", "Full-stack developer")
        )
    }
}