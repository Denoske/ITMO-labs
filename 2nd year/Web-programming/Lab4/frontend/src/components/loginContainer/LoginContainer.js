import React from 'react';
import { useForm } from "react-hook-form";
import Title from '../Title';
import {useDispatch} from 'react-redux';
import { setToken } from '../../slices/tokenSlice.js';
import {Link, useNavigate} from 'react-router-dom';


const LoginContainer = ({serverPort}) => {
  const {
    register,
    handleSubmit,
    // watch,
    formState: { errors }
  } = useForm();

  const dispatch = useDispatch()

  const navigate = useNavigate();

  let loginAction = (data) => {

  sendLoginRequest(serverPort, data.login, data.password).then((token) => {
    console.log("Resived token for autorization: " + token);
    dispatch(setToken(token));
    navigate('/main', {replace: true});
  }).catch(() => {
    console.log("Не удается запросить токен, возможно, логин или пароль неверны!");
    alert("Не удается запросить токен, возможно, логин или пароль неверны!");
  });

  }

  return <form className="login_form container" onSubmit={handleSubmit(loginAction)} >
    <Title text="Вход"/>
    <label>Логин</label>
    <input placeholder='Логин: Не менее восьми символов'
    {...register("login", {required: true, pattern: /^[A-Za-z0-9]+$/i, })} />
    {errors?.login?.type === "pattern" && ( <p className='error'>Латинские буквы и цифры</p>)}
    {errors?.login?.type === "required" && <p className='error'>Это поле является обязательным</p>}

    <label>Пароль</label>
    <input type="password" placeholder='Пароль: Не менее восьми символов'
    {...register("password", { required: true, pattern: /^[A-Za-z0-9]+$/i, minLength: 8,})} />
    {errors?.password?.type === "pattern" && (<p className='error'>Латинские буквы и цифры</p>)}
    {errors?.password?.type === "minLength" && <p className='error'>Не менее 8 символов</p>}
    {errors?.password?.type === "required" && <p className='error'>Это поле является обязательным</p>}
    
    <input type="submit" value='Войти' className='btn btn-block'/>
    <p>
      <Link className='swich_link' to="/register">Зарегистрироваться</Link>
    </p>
  </form>;
};

export default LoginContainer;

let sendLoginRequest = async (port, login, password) => {
  let url = "http://localhost:"+ port +"/auth/login?" + new URLSearchParams({"login":login, "password":password});
  console.log("Отправка запроса GET на URL: " + url);
  const response = await fetch(url, {
    method: 'GET',
    mode: 'cors',
  });

  let json = await response.json();
  console.log(json);
  return json.token;
}
