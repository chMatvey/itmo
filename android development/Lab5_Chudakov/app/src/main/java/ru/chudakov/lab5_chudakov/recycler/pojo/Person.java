package ru.chudakov.lab5_chudakov.recycler.pojo;

public class Person {

    private String name;

    private int photoId;

    private String nationality;

    public Person(String name, int photoId, String nationality) {
        this.name = name;
        this.photoId = photoId;
        this.nationality = nationality;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPhotoId() {
        return photoId;
    }

    public void setPhotoId(int photoId) {
        this.photoId = photoId;
    }

    public String getNationality() {
        return nationality;
    }

    public void setNationality(String nationality) {
        this.nationality = nationality;
    }
}
