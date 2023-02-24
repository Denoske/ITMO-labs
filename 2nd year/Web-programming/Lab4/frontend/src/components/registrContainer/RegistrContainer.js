import React, {useRef} from 'react';
import Title from '../Title';
import { useForm } from "react-hook-form";
import {useDispatch} from 'react-redux';
import { setToken } from '../../slices/tokenSlice.js';
import {Link, useNavigate} from 'react-router-dom';

const RegistrContainer = ({serverPort}) => {
    const dispatch = useDispatch()
    const navigate = useNavigate();

    const {
        register,
        handleSubmit,
        watch,
        formState: { errors }
      } = useForm();

    const password = useRef({});
    password.current = watch("password", "");
  
    const onSubmit = (data) => {
  
      console.log("Попытка, введенная пользователем:");
      console.log(data);
  
      tryToSendAddAttemptRequest(serverPort, {login:data.login, password:data.password}).then(
      (registrationResult) => {
          console.log("Получил эту попытку с сервера:" + registrationResult);
          if(registrationResult === "Пользователь успешно добавлен"){
            sendLoginRequest(serverPort, data.login, data.password).then((token) => {
                console.log("Полученный токен для авторизации: " + token);
                dispatch(setToken(token));
                navigate('/main', {replace: true});
              }
              ).catch(() => {
                console.log("Не удается запросить токен, возможно, логин или пароль неверны!");
                alert("Не удается запросить токен, возможно, логин или пароль неверны!");
              });
          } else{
              alert(registrationResult);
          }
        }
        ).catch(() => {

        console.log("Попытка добавления завершилась ошибкой!");
          alert("Попытка добавления завершилась ошибкой!");
        }
      );
    };

    return (
        <form className="register_box container" onSubmit={handleSubmit(onSubmit)}>
          <Title text='Регистрация'/>
          <label>Логин</label>
          <input placeholder='Логин: Не менее восьми символов'
              {...register("login", {required: true, pattern: /^[A-Za-z0-9]+$/i, })} />
          {errors?.login?.type === "pattern" && ( <p className='error'>Латинские буквы и цифры</p>)}
          {errors?.login?.type === "minLength" && <p className='error'>Не менее восьми символов</p>}
          {errors?.login?.type === "required" && <p className='error'>Это поле является обязательным</p>}
    
          <label>Пароль</label>
          <input type="password" placeholder='Пароль: Не менее восьми символов'
          {...register("password", { required: true, pattern: /^[A-Za-z0-9]+$/i, minLength: 8,})} />
          {errors?.password?.type === "pattern" && (<p className='error'>Латинские буквы и цифры</p>)}
          {errors?.password?.type === "minLength" && <p className='error'>Не менее восьми символов</p>}
          {errors?.password?.type === "required" && <p className='error'>Это поле является обязательным</p>}
    
    
          <label>Повторите пароль</label>
          <input type="password" placeholder='Повторите пароль'
          {...register("repeatePassword", {
               required: true,
               pattern: /^[A-Za-z0-9]+$/i,
                minLength: 8,
                validate: value => value === password.current})} />
          {errors?.repeatePassword?.type === "pattern" && (<p className='error'>Латинские буквы и цифры</p>)}
          {errors?.repeatePassword?.type === "minLength" && <p className='error'>Не менее восьми символов</p>}
          {errors?.repeatePassword?.type === "required" && <p className='error'>Это поле является обязательным</p>}
          {errors?.repeatePassword?.type === "validate" && <p className='error'>Пароли не совпадают</p>}
    
          <input type="submit" value="Зарегистрироваться" className='btn-block btn' />

            <Link className='swich_link' to="/">Уже зарегистрированы?</Link>
        </form>
    );
};

export default RegistrContainer;

let tryToSendAddAttemptRequest = async (port, data) => {
    console.log(port);
    let url = "http://localhost:"+ port +"/auth/register";
    console.log("Sending POST request to url: " + url + ". With body: " + JSON.stringify(data));
    const response = await fetch(url, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      mode: 'cors',
      body: JSON.stringify(data),
    });
    return response.text();
}

let sendLoginRequest = async (port, login, password) => {
    let url = "http://localhost:"+ port +"/auth/login?" + new URLSearchParams({"login":login, "password":password});
    console.log("Отправка запроса GET на URL:" + url);
    const response = await fetch(url, {
      method: 'GET',
      mode: 'cors',
    });
  
    let json = await response.json();
    console.log(json);
    return json.token;
  }
  
