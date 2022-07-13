// import { createApp } from 'petite-vue';
// import { createApp, reactive } from 'https://unpkg.com/petite-vue?module'

import './style.scss';

PetiteVue.createApp({
    pause: false,

    doRequest(remote, btn, repeat) {
        if (! repeat) {
            repeat = 1;
        }

        this.pause = true;

        let host = `${window.location.protocol}//${window.location.host}`;

        if (process.env.NODE_ENV === 'development') {
            host = `http://${process.env.IP}`;
        }

        fetch(`${host}/api/${remote}?btn=${btn}&repeat=${repeat}`)
            .then((resp) => {
                setTimeout(() => this.pause = false, 1000);
            })
            .catch((error) => console.log(error));
    }
}).mount()