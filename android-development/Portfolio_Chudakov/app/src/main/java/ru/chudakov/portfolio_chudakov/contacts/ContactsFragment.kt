package ru.chudakov.portfolio_chudakov.contacts

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import android.widget.Toast
import androidx.fragment.app.Fragment
import kotlinx.android.synthetic.main.fragment_contacts.view.*
import ru.chudakov.portfolio_chudakov.R

class ContactsFragment : Fragment() {

    private val mailErrorMessage = "Your phone have no app can send mail"

    private val webErrorMessage = "Your phone have no app can open web page"

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        activity?.findViewById<TextView>(R.id.toolbarTitle)?.setText(R.string.contacts)

        val root = inflater.inflate(R.layout.fragment_contacts, container, false)

        val mailIntent = Intent(Intent.ACTION_SENDTO, Uri.parse("mailto:"))
            .putExtra(Intent.EXTRA_EMAIL, arrayOf("matvey.chudakov@yandex.ru"))
        val vkIntent = Intent(Intent.ACTION_VIEW, Uri.parse("https://vk.com/"));
        val gitHubIntent = Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/chMatvey/"))
        val telegramIntent = Intent(Intent.ACTION_VIEW, Uri.parse("https://tlgrm.ru/"))

        root.mail.setOnClickListener {
            if (isIntentSafe(mailIntent)) {
                startActivity(mailIntent)
            } else {
                Toast.makeText(context, mailErrorMessage, Toast.LENGTH_SHORT).show()
            }
        }
        root.vk.setOnClickListener {
            if (isIntentSafe(vkIntent)) {
                startActivity(vkIntent)
            } else {
                Toast.makeText(context, webErrorMessage, Toast.LENGTH_SHORT).show()
            }
        }
        root.github.setOnClickListener {
            if (isIntentSafe(gitHubIntent)) {
                startActivity(gitHubIntent)
            } else {
                Toast.makeText(context, webErrorMessage, Toast.LENGTH_SHORT).show()
            }
        }
        root.telegram.setOnClickListener {
            if (isIntentSafe(telegramIntent)) {
                startActivity(telegramIntent)
            } else {
                Toast.makeText(context, webErrorMessage, Toast.LENGTH_SHORT).show()
            }
        }

        return root
    }

    private fun isIntentSafe(intent: Intent): Boolean {
        val packageManager = activity?.packageManager
        val activities = packageManager?.queryIntentActivities(intent, 0)

        return activities!!.size > 0
    }
}