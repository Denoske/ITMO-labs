var r_selected = false;

function validate_by_id(id, min, max, id_to_disable) {
    const input = document.getElementById(id);
    const disable = document.getElementById(id_to_disable);
    const submit = document.getElementById('input_form:submit');
    const is_parsed = try_parse(input.value);
    if (is_parsed[0] && min <= is_parsed[1] && is_parsed[1] <= max) {
        disable.className = "";
        return true;
    } else {
        disable.className = "incorrect";
        return false;
    }
}

function validate()
{
    let fl = true;
    const submit = document.getElementById('input_form:submit');
    fl &= validate_by_id('input_form:x', -5, 5, 'input_form:x');
    fl &= r_selected;
    submit.disabled = !fl;
    return fl;
}

function try_parse(x) {
    try {
        const a = parseFloat(x);
        const reg = new RegExp("^-?\\d*\\.?\\d*$");
        if (isNaN(a) || !reg.test(x))
            return [false];
        return [true, a];
    } catch (exc) {
        return [false];
    }
}

function point_clicked(e)
{
    if (!r_selected)
    {
        alert("You must select R...")
        return;
    }
    const element = document.getElementById('graph');
    const click_x = e.clientX, click_y = e.clientY;
    const pos = element.getBoundingClientRect();
    const screen_x = pos.x, screen_y = pos.y;
    const scale = (element.getBoundingClientRect().width / 100);
    const x = ((click_x - screen_x) / scale - 50) / 8, y = -((click_y - screen_y) / scale - 50) / 8;
    console.log(click_x, click_y);
    console.log(screen_x, screen_y);
    console.log(x, y);

    document.getElementById('input_form:x').value = x;
    document.getElementById('input_form:y_text').value = y;
    if (validate())
    {
        document.getElementById('input_form:submit').click();
    }
}

function loaded(circles_raw)
{
    validate();
    document.getElementById('graph').addEventListener("click", point_clicked, false);


}

function redrawGraph(circles_raw)
{
    const svgns = "http://www.w3.org/2000/svg";
    let circles = eval(circles_raw);
    document.getElementById('graph').innerHTML = '';

    for (let i = 0; i < circles.length; ++i)
    {
        let coords = circles[i];
        let circle = document.createElementNS(svgns, 'circle');
        let x_1 = coords[0];
        let x_2 = parseFloat(coords[1]);
        let y_1 = coords[2];
        let y_2 = parseFloat(coords[3]);
        let x = x_1 + (x_2/(10**x_2.toString().length));
        let y = y_1 + (y_2/(10**y_2.toString().length));
        let r_val_circle = coords[4];
        circle.setAttribute('class', 'circle_html');
        circle.setAttribute('cx', `${50 + x * 8}%`);
        circle.setAttribute('cy', `${50 - y * 8}%`);
        circle.setAttribute('r', '2%');
        circle.setAttribute('r_value', `${r_val_circle}`);
        circle.setAttribute('fill', `${coords[5] ? 'green' : 'red'}`);
        document.getElementById('graph').appendChild(circle);
    }
}

function r_change(r) {
    const r_val = parseInt(r.value);
    document.getElementById('draw').setAttribute("style", "scale: " + 20 * r_val + "%; top: 0; position: absolute");
    r_selected = true;
    validate();
    let ok = document.getElementsByClassName('circle_html');
    for (let i = 0; i < ok.length;i++) {
        let r_graf = ok[i].attributes[4].value;
        if (r_graf > r_val) {
            ok[i].attributes[5].value = 'red';
        }else ok[i].attributes[5].value = 'green';

    }

}