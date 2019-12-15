package ru.chudakov.lab6_chudakov.dto;

public class PlaylistItemDTO {
    private String id;

    private SnippetDTO snippet;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public SnippetDTO getSnippet() {
        return snippet;
    }

    public void setSnippet(SnippetDTO snippet) {
        this.snippet = snippet;
    }
}
