package ru.chudakov.lab6_chudakov.dto;

public class SnippetDTO {
    private String title;

    private ResourceIdDTO resourceId;

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public ResourceIdDTO getResourceId() {
        return resourceId;
    }

    public void setResourceId(ResourceIdDTO resourceId) {
        this.resourceId = resourceId;
    }
}
