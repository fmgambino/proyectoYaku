<main class=" container-fluid" style="overflow-y:scroll;">

    <div class="">

        <div class="row">
            <!-- columna1  -->
            <div class="col-4 ">
                <div class=" form-inline">
                    <div class="col-6" style="padding-left: 0px; padding-right: 7px;">
                        <div class="mdl-card--expand color-azul-1 text-center pb-3" style="height: 109px;">
                            <h4 class=" hc-color-text-blanco ">Extractor</h4>
                            <div class=" form-inline d-flex " style="justify-content: center;">
                                <!-- SWITCH-->
                                <label class="switch mr-2">
                                    <input onchange="sw1_change()" type="checkbox" id="display_sw1">
                                    <span class="slider round"></span>
                                </label>
                                <img src="<?php echo base_url('images/cancel.png') ?>" class="hc-icono-cancel ml-2"
                                    id="icono1" alt="">
                            </div>
                        </div>
                    </div>
                    <div class="col-6" style="padding-right: 0px; padding-left: 7px;">
                        <div class="mdl-card--expand color-azul-1 text-center pb-3" style="height: 109px;">
                            <h4 class=" hc-color-text-blanco  ">Nivel Bateria</h4>
                            <div class="form-inline" style="display: inline-flex">
                                <div class="progress" style="   width: 80px;height: 30px; border: 2px solid white;">
                                    <div id="bateria" class="progress-bar progress-bar-striped progress-bar-animated" role="progressbar" style="width: 90% ; background-color: #2cff00 !important; " aria-valuenow="25"
                                        aria-valuemin="0" aria-valuemax="100">
                                        <h4 style="margin: auto;">50%</h4>
                                    </div>
                                </div>
                                <div class="progress" style="   width: 10px;height: 20px; border-radius: 0; border: 2px solid white;">
                                    <div class="progress-bar" role="progressbar" style="width: 0% " aria-valuenow="0"
                                        aria-valuemin="0" aria-valuemax="100"></div>
                                </div>
                            </div>

                        </div>
                    </div>
                </div>
                <div class=" ">
                    <div class=" mdl-card--expand color-azul-1 ">
                        <div class="form-inline">
                            <div class="col-6 hc-color-text-blanco ">
                                <div class="col-12 form-inline " style="justify-content: center;">
                                    <h4 class=" mb-0 ">Volumen</h4>
                                    <img src="<?php echo base_url('images/iconoWater.svg') ?>" class="icono">
                                </div>
                                <div class="col-12 form-inline mt-3" style="justify-content: center;">
                                    <p id="valorVolumen" class="weather-temperature mr-1">--</p>
                                    <h4 class="hc-unidades">%</h4>
                                </div>
                            </div>
                            <div class="col-6 " style="width: 100%; height: 130px;">
                                <div id="gaugeVolumen"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <!--columna 2-->
            <div class="col-4 ">

                <div class=" ">

                    <div class=" mdl-card--expand color-azul-1 ">
                        <div class="form-inline">
                            <div class=" col-6 hc-color-text-blanco ">
                                <div class="col-12 form-inline text-center ">
                                    <h4 class=" mb-0 ">Temperatura</h4>
                                    <img src="<?php echo base_url('images/iconoTemp.svg') ?>" class="icono">
                                </div>
                                <div class="col-12 form-inline mt-3">
                                    <p id="valorTemperatura" class="weather-temperature hc-valor mr-1">--</p>
                                    <h4 class="hc-unidades">°C</h4>
                                </div>
                            </div>

                            <div class="col-6 " style="width: 100%; height: 80px;">
                                <div id="gaugeTemperatura"></div>
                            </div>
                        </div>


                    </div>
                </div>


                <div class=" ">
                    <div class=" mdl-card--expand color-azul-1 ">
                        <div class="form-inline">
                            <div class="col-6 hc-color-text-blanco ">
                                <div class="col-12 form-inline " style="justify-content: center;">
                                    <h4 class=" mb-0 ">Humedad</h4>
                                    <img src="<?php echo base_url('images/iconoWater.svg') ?>" class="icono">
                                </div>
                                <div class="col-12 form-inline mt-3" style="justify-content: center;">
                                    <p id="valorHumedad" class="weather-temperature mr-1">--</p>
                                    <h4 class="hc-unidades">%</h4>
                                </div>
                            </div>
                            <div class="col-6 " style="width: 100%; height: 130px;">
                                <div id="gaugeHumedad"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <!-- Espuma -->
            <div class="col-4 ">
                <div class=" ">

                    <div class=" mdl-card--expand color-azul-1 ">
                        <div class="form-inline">
                            <div class=" col-6 hc-color-text-blanco ">
                                <div class="col-12 form-inline " style="justify-content: center;">
                                    <h4 class=" mb-0 ">Viento</h4>
                                    <img src="<?php echo base_url('images/iconoViento.svg') ?>" class="icono">
                                </div>
                                <div class="col-12 form-inline mt-3 " style="justify-content: center;">
                                    <p id="valorViento" class="weather-temperature mr-1 ">23.11</p>
                                    <h4 class="hc-unidades">km/h</h4>
                                </div>
                            </div>

                            <div class="col-6 " style="width: 100%; height: 80px;">
                                <div id="gaugeViento"></div>
                            </div>
                        </div>
                    </div>

                </div>
                <div class=" ">
                    <div class=" mdl-card--expand color-azul-1 ">
                        <div class="form-inline">
                            <div class="col-6 hc-color-text-blanco ">
                                <div class="col-12 form-inline " style="justify-content: center;">
                                    <h4 class=" mb-0 ">Ph H2O</h4>
                                    <img src="<?php echo base_url('images/iconoWater.svg') ?>" class="icono">
                                </div>
                                <div class="col-12 form-inline mt-3" style="justify-content: center;">
                                    <p id="valorPh" class="weather-temperature mr-1">--</p>

                                </div>
                            </div>
                            <div class="col-6 " style="width: 100%; height: 130px;">
                                <div id="gaugePh"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>


        </div>
        <div class=" form-inline ">
            <div class="col-6 pl-0">
                <div id="grafico1" class="color-azul-1 pl-3 " style=" height: 350px;padding-top: 40px !important;">
                </div>
            </div>
            <div class="col-6 pr-0">
                <div id="grafico2" class="color-azul-1 pl-3" style=" height: 350px;padding-top: 40px !important;"></div>
            </div>
        </div>
        <div class="col-12 col-md-4 hc-box-a">
            <div class="mdl-card  trending">
                <div>
                    <span class="mdl-list__item-secondary-content" style="padding-top: 6px;">
                    </span>
                </div>
            </div>
        </div>
        <!-- Actuadores-->
        <div class="row">

        </div>
    </div>
    </div>
</main>

<!-- <script src="<?php echo base_url('js/progresbarlmz.js') ?>"></script> -->
<script src="<?php echo base_url('js/graficos.js') ?>"></script>

<script>
/*
const options = {
    connectTimeout: 1000,
    // Authentication
    clientId: 'client_id_' + Math.floor((Math.random() * 1000000) + 1),
    username: '<?php echo MQTT_USER; ?>',
    password: '<?php echo MQTT_PASSWORD; ?>',
    keepalive: 60,
    clean: true,
}*/

// WebSocket connect url
/*const WebSocket_URL = 'wss://broker.emqx.io:8084/mqtt';
const client = mqtt.connect(WebSocket_URL, options)

var device_topic = '<?php echo ROOT_TOPIC . "/" . $_SESSION['selected_topic'] . "/" ?>';
client.on('connect', () => {
    console.log('Conexión Exitosa ^_^');

    client.subscribe(device_topic + "data", {
        qos: 0
    }, (error) => {
        if (error) {
            console.log("Error al Suscribir");
        } else {
            console.log("Suscrito al Broker con Exito!");
            console.log("Proyecto de Inversión");
            console.log("San Miguel de Tucumán - Tucumán - Argentina");
            console.log("2025");
        }

    })
})
*/

console.log('<?php echo base_url()?>')

var contCo2 = 0;
var contcdtv = 0;

var sumadorA = 0;
var sumadorB = 0;
var sumadorC = 0;
var co2, cdtv;

console.log("llegue aqui 2");

client.on('message', (topic, message) => {
    console.log('Msg desde el topico: ', topic, ' ----> ', message.toString());

})

client.on('reconnect', (error) => {
    console.log('reconnecting:', error);
})

client.on('error', (error) => {
    console.log('Connect Error:', error);
})

var img1 = "<?php echo base_url('images/cancelblanco.png') ?>";
var img2 = "<?php echo base_url('images/checkblanco.png') ?>";

function sw1_change() {
    var imagen1 = document.getElementById('icono1');
    if ($('#display_sw1').is(":checked")) {
        console.log("ingrese en sw1_change ok");
        client.publish(device_topic + 'actions/sw1', "1"); //Valor que envio al broker             
        imagen1.src = img2;
        imagen1.classList.remove("hc-icono-cancel");
        imagen1.classList.add("hc-icono-check");
    } else {
        console.log("ingrese en sw1_change else");
        client.publish(device_topic + 'actions/sw1', "0");
        imagen1.src = img1;
        imagen1.classList.remove("hc-icono-check");
        imagen1.classList.add("hc-icono-cancel");
    }
}

var bat100 = "<?php echo base_url('images/icons/iconoBateria100.svg') ?>";
var bat75 = "<?php echo base_url('images/icons/iconoBateria75.svg')  ?>";
var bat50 = "<?php echo base_url('images/icons/iconoBateria50.svg')  ?>";
var bat25 = "<?php echo base_url('images/icons/iconoBateria25.svg')  ?>";
var NivelBateria = 40;


console.log(document.getElementById('bateria'));

if (NivelBateria > 75) {
    document.getElementById('bateria').src = bat100;
} else {
    if (NivelBateria > 50) {
        document.getElementById('bateria').src = bat75;
    } else {
        if (NivelBateria > 25) {
            document.getElementById('bateria').src = bat50;
        } else {
            document.getElementById('bateria').src = bat25;
        }
    }
}

// FUNCIONES CIRCULOS DE ESTADOS

function ce1_change() {
    if ($('#display_sw1').is(":checked")) {
        client.publish(device_topic + 'actions/sw1', "1"); //Valor que envio al broker
    } else {
        client.publish(device_topic + 'actions/sw1', "0");
    }
}
</script>