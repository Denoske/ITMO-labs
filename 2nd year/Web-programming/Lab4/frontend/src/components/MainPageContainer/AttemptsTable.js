import React from 'react';
import { useSelector} from 'react-redux';
import { selectAttempts } from '../../slices/AttemptSlice';

const AttemptsTable = () => {
  const attempts =  useSelector(selectAttempts);
  let i = 0;

  return(
    <table className='attempts-table container'>
      <thead>
        <tr><th>X</th><th>Y</th><th>R</th><th>Result</th></tr>
      </thead>
      <tbody>
        {attempts!== null && attempts.map((attempt) => {
          return (
            // id={i++} key={i++}
            <tr key={i++}>
              <td>{round(attempt.x)}</td>
              <td>{round(attempt.y)}</td>
              <td>{round(attempt.r)}</td>
              <td>{attempt.doFitArea ? "True" : "False"}</td>
            </tr>
        );
        })}
          
      </tbody>
    </table>
  );
};

let round = (val) => {
  return Math.round(val * 100) / 100;
}

export default AttemptsTable;
