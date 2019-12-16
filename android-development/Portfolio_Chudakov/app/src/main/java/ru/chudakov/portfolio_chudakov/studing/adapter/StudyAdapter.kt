package ru.chudakov.portfolio_chudakov.studing.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.study_items.view.*
import ru.chudakov.portfolio_chudakov.R
import ru.chudakov.portfolio_chudakov.studing.pojo.Institution

class StudyAdapter(private val items: List<Institution>) : RecyclerView.Adapter<StudyAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        val view = inflater.inflate(R.layout.study_items, parent, false)

        return ViewHolder(view)
    }

    override fun getItemCount(): Int = items.size

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val institution = items[position]

        holder.image.setImageResource(institution.imgResource)
        holder.name.text = institution.name
        holder.date.text = institution.date
        holder.description.text = institution.description
    }

    class ViewHolder (view: View) : RecyclerView.ViewHolder(view) {
        val image: ImageView = view.studyImg

        val name: TextView = view.studyName

        val date: TextView = view.studyDate

        val description: TextView = view.studyDescription
    }
}