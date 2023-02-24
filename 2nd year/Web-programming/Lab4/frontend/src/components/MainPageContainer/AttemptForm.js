import React, {useEffect} from 'react';
import Title from '../Title';
import { useForm } from "react-hook-form";
import { useSelector, useDispatch } from 'react-redux';
import {addAttempt, selectAttempts} from '../../slices/AttemptSlice';
import { selectToken } from '../../slices/tokenSlice';


const AttemptForm = ({serverPort}) => {
  const token =  useSelector(selectToken);
  const dispatch = useDispatch();

  const {
    register,
    handleSubmit,
    // watch,
    formState: { errors }
  } = useForm();

  const onSubmit = (data) => {
    console.log(token);

    console.log("Попытка, введенная пользователем:");
    console.log(data);

    tryToSendAddAttemptRequest(serverPort, token, data).then(
    (newAttempt) => {
        console.log("Получил эту попытку с сервера:");
        console.log(newAttempt);
        dispatch(addAttempt(newAttempt));
        }
      ).catch(() => {
      console.log("Попытка добавления завершилась ошибкой!");
        alert("Попытка добавления завершилась ошибкой! выйдите, пожалуйста...");

      }
    );
  };

    const options = [
        { value: '-2', label: '-2' },
        { value: '-1', label: '-1' },
        { value: '3', label: '3' }
    ]


  // console.log(watch("example")); you can watch individual input by pass the name of the input

  return (
    <form className="attempt_form container" onSubmit={handleSubmit(onSubmit)}>
      <Title text='Введите координаты'/>
      {/* <label>X</label> */}
        <p >X:</p>
      <input placeholder='X: от -4 до 4'
          {...register("x", {required: true, pattern: /^-?[0-9]+$/i, min: -4, max: 4 })} />
      {errors.x && (
        <p className='error'>X должен быть от -4 до 4</p>
      )}

        <p >Y:</p>
        <input placeholder='y: от -5 до 5'
               {...register("y", {required: true, pattern: /^-?[0-9]+$/i, min: -5, max: 5 })} />

      {errors.y && (
        <p className='error'> Y должен быть от -5 до 5</p>
      )}

        <p >R:</p>
        <select  id= "Rval" placeholder='R: от 1 до 5' {...register("r", {required: true, onChange:(e)=>{
                console.log("changed r")
                //UpdatePlot();
              } },)}>
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
        </select>

        {errors.r && (
            <p className='error'>R должен быть от 1 до 5</p>
        )}



      <input type="submit" value="Отправить" className='btn-block btn' />
    </form>
  );

}

export default AttemptForm;


let tryToSendAddAttemptRequest = async (port, token, data) => {
  console.log(port);
  let url = "http://localhost:"+ port +"/attempts";
  console.log("Отправка запроса POST на url: " + url + ". С телом:" + JSON.stringify(data));
  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': "Bearer " + token
    },
    mode: 'cors',
    body: JSON.stringify(data),
  });
  return await response.json();
}