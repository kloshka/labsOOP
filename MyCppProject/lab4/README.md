Лабораторная работа № 04
ВАРИАНТ 29 Ромб 5-угольник 6-угольник
Тема: Основы метапрограммирования
Цель:
• Изучение основ работы с шаблонами (template) в С++;
• Изучение шаблонов умных указателей
Порядок выполнения работы
1. Ознакомиться с теоретическим материалом.
2. Получить у преподавателя вариант задания.
3. Реализовать задание своего варианта в соответствии с поставленными требованиями.
4. Подготовить тестовые наборы данных.
5. Создать репозиторий на GitHub.
6. Отправить файлы лабораторной работы в репозиторий.
7. Отчитаться по выполненной работе путём демонстрации работающей программы на тестовых наборах данных
(как подготовленных самостоятельно, так и предложенных преподавателем) и ответов на вопросы
преподавателя (как из числа контрольных, так и по реализации программы).
Требования к программе
Разработать шаблоны классов согласно варианту задания. Параметром шаблона должен являться скалярный тип
данных задающий тип данных для оси координат.
Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника (эти
фигуры просто должны быть вписаны в круг). Для хранения координат фигур необходимо реализовать свой шаблон
template <class T> Point,в качестве параметра шаблона должен быть тип для переменных координат. Проверку на
то что тип T скалярный реализовать с помощью concept.
Разработать классы согласно варианту задания, классы должны наследоваться от базового шаблонного класса
Figure<T>, где T скалярный тип подставляющийся в Point. При этом сами точки должны хранится в виде умных
указателей std::unique_ptr<Point<T>> Все классы должны поддерживать набор общих методов из предыдущей
лабораторной работы.
Создать программу, которая позволяет:
• Запрещается использовать сырые указатели
• Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
• Динамический массив должен быть сделан в виде шаблона (параметр шаблона – класс для хранения в
массиве template <class T> Array {…})
• Сохранять созданные фигуры в динамический массив (переиспользовать от предыдущей лабораторной
работы) умных указатели на фигуру (std::shared_ptr<T[]>)
• Фигуры должны иметь переопределенные операции копирования, сравнения и приведение к типу double
(вычисление площади)
• Вызывать для всего массива общие функции (1-3 см. выше). Т.е. распечатывать для каждой фигуры в
массиве геометрический центр, координаты вершин и площадь.
• Необходимо уметь вычислять общую площадь фигур в массиве.
• Удалять из массива фигуру по индексу;
• При увеличении емкости копирования должна использоваться операция перемещения (move) для
элементов массива (при перемещении из массива меньшего размера в массив большего размера)
• Программа должна содержать примеры работы с шаблоном массива как для базового типа Figure*
(например, проверить для Array<Figure<int>*>) так и для типов наследников, например Square
(Array<Square<int>>)
