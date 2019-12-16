package ru.chudakov.portfolio_chudakov.job.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.job_items.view.*
import ru.chudakov.portfolio_chudakov.R
import ru.chudakov.portfolio_chudakov.job.pojo.Job

class JobAdapter(private val items: List<Job>) : RecyclerView.Adapter<JobAdapter.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view = inflater.inflate(R.layout.job_items, parent, false)

        return ViewHolder(view)
    }

    override fun getItemCount(): Int = items.size

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val job = items[position]

        holder.image.setImageResource(job.imgResource)
        holder.name.text = job.name
        holder.date.text = job.date
        holder.position.text = job.position
    }


    class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val image: ImageView = view.jobImg

        val name: TextView = view.jobName

        val date: TextView = view.jobDate

        val position: TextView = view.jobPosition
    }
}