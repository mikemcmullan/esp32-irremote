// import { createApp } from 'petite-vue';
// import { createApp, reactive } from 'https://unpkg.com/petite-vue?module'

import './style.scss';

PetiteVue.createApp({
    pause: false,

    doRequest(btn, repeat) {
        if (! repeat) {
            repeat = 1;
        }

        this.pause = true;

        fetch(`http://192.168.1.130/api?btn=${btn}&repeat=${repeat}`)
            .then((resp) => {
                setTimeout(() => this.pause = false, 1000);
            })
            .catch((error) => console.log(error));
    }
}).mount()