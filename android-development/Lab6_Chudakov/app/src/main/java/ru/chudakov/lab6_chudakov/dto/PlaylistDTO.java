package ru.chudakov.lab6_chudakov.dto;

import java.util.List;

public class PlaylistDTO {
    private List<PlaylistItemDTO> items;

    public List<PlaylistItemDTO> getItems() {
        return items;
    }

    public void setItems(List<PlaylistItemDTO> items) {
        this.items = items;
    }
}
